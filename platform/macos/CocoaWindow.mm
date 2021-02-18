#include "CocoaWindow.h"

#include "main/events/EventQueue.h"
#include "main/events/AppEvent.h"

#include "platform/macos/CocoaContext.h"

#include <Cocoa/Cocoa.h>

@interface PWindow : NSWindow
@end

@implementation PWindow
- (BOOL) acceptsMouseMovedEvents
{
  return YES;
}
@end

@interface PWindowDelegate : NSObject <NSWindowDelegate>
{
  Papaya::Ref<Papaya::CocoaContext> context;
  Papaya::RenderApi::API api;
}

- (instancetype) init: (Papaya::RenderApi::API) type;
- (void) setContext: (Papaya::Ref<Papaya::CocoaContext>) ctx;
@end

@implementation PWindowDelegate

- (instancetype) init: (Papaya::RenderApi::API) type
{
  if (self = [super init])
  {
    api = type;
  }
  
  return self;
}

- (void) setContext: (Papaya::Ref<Papaya::CocoaContext>) ctx
{
  context = ctx;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowCloseEvent>());
  return NO;
}

- (void)windowDidResize:(NSNotification *)sender
{
  NSWindow* object = [sender object];

  if (api == Papaya::RenderApi::API::OpenGL)
    std::static_pointer_cast<Papaya::CocoaOpenGLContext>(context)->OnResize();

  NSRect content = [object contentRectForFrameRect:[object frame]];
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(content.size.width, content.size.height));
}

- (NSSize)window:(NSWindow *)window
willUseFullScreenContentSize:(NSSize)proposedSize
{
    if (api == Papaya::RenderApi::API::OpenGL)
        std::static_pointer_cast<Papaya::CocoaOpenGLContext>(context)->OnResize();
    
    Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(proposedSize.width, proposedSize.height));
    return proposedSize;
}

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
  if (api == Papaya::RenderApi::API::OpenGL)
    std::static_pointer_cast<Papaya::CocoaOpenGLContext>(context)->OnResize();
    
  NSWindow* sender = [notification object];
  NSRect content = [sender contentRectForFrameRect:[sender frame]];
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(content.size.width, content.size.height));
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowFocusEvent>());
}

- (void)windowDidResignKey:(NSNotification *)notification
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowLoseFocusEvent>());
}

@end

namespace Papaya {

CocoaWindow::CocoaWindow(const WindowAttribs& attribs) {

  m_Attribs = attribs;

  // Create Window Frame
  int width = attribs.Width > 0 ? attribs.Width : 800;
  int height = attribs.Height > 0 ? attribs.Height : 800;
  NSRect frame = NSMakeRect(0.0, 0.0, width, height);

  // Create Style Specifications
  int styleMask = NSWindowStyleMaskClosable |
                  NSWindowStyleMaskTitled |
                  NSWindowStyleMaskMiniaturizable;
                
  if (attribs.Resizable)
    styleMask |= NSWindowStyleMaskResizable;

  NSString* title = @(attribs.Title.Raw());

  // Create Delegate
  m_Delegate = [[PWindowDelegate alloc] init: attribs.Api];

  // Create Window
  m_Window = [[PWindow alloc] initWithContentRect: frame
                                       styleMask: styleMask
                                         backing: NSBackingStoreBuffered
                                           defer: NO];

  [(PWindow *)m_Window setTitle: title];
  [(PWindow *)m_Window setDelegate: (PWindowDelegate *) m_Delegate];
  [(PWindow *)m_Window center];

  ((PWindow *)m_Window).preservesContentDuringLiveResize = NO;
}

CocoaWindow::~CocoaWindow() {
  [(PWindow *)m_Window setDelegate: nil];
  [(PWindowDelegate *)m_Delegate release];
  m_Delegate = nullptr;

  [(PWindow *)m_Window close];
  [(PWindow *)m_Window release];
  m_Window = nullptr;
}

void CocoaWindow::Show() {
  [(PWindow *)m_Window makeKeyAndOrderFront: nil];
}

void CocoaWindow::Hide() {
  [(PWindow *)m_Window orderOut:nil];
}

void CocoaWindow::Close() {
  [(PWindow *)m_Window close];
}

void CocoaWindow::SetContext(const Ref<Context>& context)
{
  m_Context = context;
  Ref<CocoaContext> ctx = std::static_pointer_cast<CocoaContext>(context);
  
  [(PWindow *)m_Window setContentView: (NSView*) ctx->m_View];
  [(PWindow *)m_Window makeFirstResponder: (NSView*) ctx->m_View];

  if (m_Attribs.Api == RenderApi::API::OpenGL) // We need to update the view once the view is set
    std::static_pointer_cast<CocoaOpenGLContext>(ctx)->OnResize();

  [(PWindowDelegate *)m_Delegate setContext: ctx]; // This method sets the window to update the context on resize
}

void CocoaWindow::OnUpdate()
{
  m_Context->SwapBuffers();
}

} // namespace Papaya
