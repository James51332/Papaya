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
@end

@implementation PWindowDelegate

- (BOOL)windowShouldClose:(NSWindow *)sender {
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowCloseEvent>());
  return NO;
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize 
{
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowResizeEvent>(frameSize.width, frameSize.height));
  return frameSize;
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
  m_Delegate = [[PWindowDelegate alloc] init];

  // Create Window
  m_Window = [[PWindow alloc] initWithContentRect: frame
                                       styleMask: styleMask
                                         backing: NSBackingStoreBuffered
                                           defer: NO];

  [(PWindow *)m_Window setTitle: title];
  [(PWindow *)m_Window setDelegate: (PWindowDelegate *) m_Delegate];
  [(PWindow *)m_Window center];
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
}

void CocoaWindow::OnUpdate()
{
  m_Context->SwapBuffers();
}

} // namespace Papaya