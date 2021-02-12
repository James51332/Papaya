#include "CocoaContext.h"

#include "main/core/Window.h"
#include "main/core/Log.h"

#include "main/events/MouseEvent.h"
#include "main/events/KeyEvent.h"
#include "main/events/EventQueue.h"

#include "platform/macos/CocoaInputCode.h"

#include <Cocoa/Cocoa.h>

////////////////////////////////////////////
///// PView ////////////////////////////////
////////////////////////////////////////////

@interface PView : NSView
{
  NSUInteger flags;
}

- (instancetype) init;
@end

@implementation PView

- (instancetype) init {
  if (self = [super initWithFrame:NSMakeRect(0.0, 0.0, 800.0, 600.0)])
  {
    flags = 0;
  }

  return self;
}

- (void)mouseDown:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::MouseLeft));
}

- (void) mouseDragged:(NSEvent *)event
{
  [self mouseMoved: event];
}

- (void) mouseUp:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::MouseLeft));
}

- (void) mouseMoved:(NSEvent *)event
{
  NSPoint location = [event locationInWindow];
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseMoveEvent>(location.x, location.y));
}

- (void) rightMouseDragged:(NSEvent *)event
{
  [self mouseMoved: event];
}

- (void) rightMouseUp:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::MouseRight));
}

- (void) rightMouseDown:(NSEvent *)event
{
  [super rightMouseDown: event];
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::MouseRight)); 
}

- (void) otherMouseDown:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MousePressEvent>(Papaya::CocoaMouseCodeToPapayaMouseCode([event buttonNumber])));
}

- (void) otherMouseDragged:(NSEvent *)event
{
  [self mouseMoved: event];
}

- (void) otherMouseUp:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseReleaseEvent>(Papaya::CocoaMouseCodeToPapayaMouseCode([event buttonNumber])));
}

- (void) scrollWheel:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::MouseScrollEvent>([event scrollingDeltaX], [event scrollingDeltaY]));
}

- (void) keyDown:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyPressEvent>(Papaya::CocoaKeyCodeToPapayaKeyCode([event keyCode])));
}

- (void) keyUp:(NSEvent *)event
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyReleaseEvent>(Papaya::CocoaKeyCodeToPapayaKeyCode([event keyCode])));
}

- (void) flagsChanged:(NSEvent *)event
{
  // TODO: A flags changed event in theory should be called everytime a flag is changed
  // and therefore only have one key pressed or released. However, I'm simply going to
  // assume this is always the case but this may not be the best approach. It's possible
  // more than one flag will change when this is called so it is worth looking into reworking
  // this function.

  Papaya::KeyCode key = Papaya::KeyNone;
  NSUInteger flag;
  NSUInteger deltaFlags = [event modifierFlags] ^ flags;

  if (deltaFlags & NSEventModifierFlagCapsLock)
  {
    flag = NSEventModifierFlagCapsLock;
    key = Papaya::KeyCaps;
  }
  else if (deltaFlags & NSEventModifierFlagShift)
  {
    flag = NSEventModifierFlagShift;
    key = Papaya::KeyShift;
  }
  else if (deltaFlags & NSEventModifierFlagControl)
  {
    flag = NSEventModifierFlagControl;
    key = Papaya::KeyCaps;
  }
  else if (deltaFlags & NSEventModifierFlagOption)
  {
    flag = NSEventModifierFlagOption;
    key = Papaya::KeyAlt;
  }
  else if (deltaFlags & NSEventModifierFlagFunction)
  {
    flag = NSEventModifierFlagFunction;
    key = Papaya::KeyFn;
  }
  else return;

  bool pressed = flag & [event modifierFlags];

  if (pressed)
    Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyPressEvent>(key));
  else
    Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::KeyReleaseEvent>(key));

  flags = [event modifierFlags];
}

- (BOOL) wantsUpdateLayer {
  return YES;
}

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL) acceptsFirstResponder {
  return YES;
}
@end

namespace Papaya
{

////////////////////////////////////////////
///// CocoaContext /////////////////////////
////////////////////////////////////////////

bool CocoaContext::s_KeyCodesInitialized = false;

Ref<Context> CocoaContext::Create(const Scope<Window>& window, RenderApi::API api)
{
  if (!s_KeyCodesInitialized)
  {
    InitCocoaInputCodes();
    s_KeyCodesInitialized = true;
  }

  switch (api)
  {
    case RenderApi::API::OpenGL: {
      return CreateRef<CocoaOpenGLContext>(window);
      break;
    }

    default: break;
  }

  PAPAYA_ASSERT(false, "Unsupported Render API! Please use OpenGL on macOS");
  return nullptr;
}

CocoaContext::~CocoaContext()
{

}

////////////////////////////////////////////
///// CocoaOpenGLContext ///////////////////
////////////////////////////////////////////

CocoaOpenGLContext::CocoaOpenGLContext(const Scope<Window>& window)
{
  m_Api = RenderApi::API::OpenGL;

  NSOpenGLPixelFormatAttribute attribs[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFADepthSize,
    32,
    NSOpenGLPFAOpenGLProfile,
    NSOpenGLProfileVersion4_1Core,
    0
  };

  NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs];
  PAPAYA_ASSERT(format, "Failed to create OpenGL Pixel Format!");

  m_Context = [[NSOpenGLContext alloc] initWithFormat: format
                                         shareContext: nil];
  PAPAYA_ASSERT(m_Context, "Failed to create OpenGL Context!");

  m_View = [[PView alloc] init];
  [(NSOpenGLContext*) m_Context setView: (PView*) m_View];

  [(NSOpenGLContext*) m_Context update];
  
  [(NSOpenGLContext*) m_Context makeCurrentContext];
  [(NSOpenGLContext*) m_Context flushBuffer];
}

CocoaOpenGLContext::~CocoaOpenGLContext()
{

}

void CocoaOpenGLContext::SwapBuffers()
{
  [(NSOpenGLContext*) m_Context flushBuffer];
}

} // namespace Papaya