#include "CocoaContext.h"

#include "main/core/Log.h"

#include "main/events/MouseEvent.h"
#include "main/events/KeyEvent.h"
#include "main/events/EventQueue.h"

#include "platform/macos/CocoaInputCode.h"

#include <Cocoa/Cocoa.h>

@interface PView : NSView

- (instancetype) init;

@end

@implementation PView

- (instancetype) init {
  self = [super initWithFrame:NSMakeRect(0.0, 0.0, 800.0, 600.0)];

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
  PAPAYA_CORE_INFO("MousePressed: {} (NSCode: {})", Papaya::CocoaMouseCodeToPapayaMouseCode([event buttonNumber]), [event buttonNumber]);
}

- (void) otherMouseDragged:(NSEvent *)event
{
  [self mouseMoved: event];
}

- (void) otherMouseUp:(NSEvent *)event
{
}

- (void) scrollWheel:(NSEvent *)event
{
  
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
  
}

- (BOOL) wantsUpdateLayer {
  return YES;
}

- (BOOL)canBecomeKeyView
{
    return YES;
}

- (void)updateLayer
{

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

Ref<Context> CocoaContext::Create(RenderApi api)
{
  if (!s_KeyCodesInitialized)
  {
    InitCocoaInputCodes();
    s_KeyCodesInitialized = true;
  }

  switch (api)
  {
    case RenderApi::OpenGL: {
      return CreateRef<CocoaOpenGLContext>();
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

CocoaOpenGLContext::CocoaOpenGLContext()
{
  m_Api = RenderApi::OpenGL;

  NSOpenGLPixelFormatAttribute attribs[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFADepthSize,
    32,
    // NSOpenGLPFAOpenGLProfile,
    // NSOpenGLProfileVersion4_1Core,
    0
  };

  NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs];
  PAPAYA_ASSERT(format, "Failed to create OpenGL Pixel Format!");

  m_Context = [[NSOpenGLContext alloc] initWithFormat: format
                                         shareContext: nil];
  PAPAYA_ASSERT(m_Context, "Failed to create OpenGL Context!");

  m_View = [[PView alloc] init];
  [(NSOpenGLContext*) m_Context setView: (PView*) m_View];

  [(NSOpenGLContext*) m_Context makeCurrentContext];
  [(NSOpenGLContext*) m_Context update];
  [(NSOpenGLContext*) m_Context flushBuffer];
}

CocoaOpenGLContext::~CocoaOpenGLContext()
{

}

void CocoaOpenGLContext::OnUpdate()
{
  [(NSOpenGLContext*) m_Context flushBuffer];
}

} // namespace Papaya