#include "CocoaWindow.h"

#include "main/events/EventQueue.h"
#include "main/events/AppEvent.h"

#include <Cocoa/Cocoa.h>

@interface PWindow : NSWindow
@end

@implementation PWindow
@end

@interface PWindowDelegate : NSObject<NSWindowDelegate>
@end

@implementation PWindowDelegate
- (BOOL)windowShouldClose:(NSWindow *)sender {
  Papaya::EventQueue::PushEvent(Papaya::CreateScope<Papaya::WindowCloseEvent>());
  return NO;
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

}

void CocoaWindow::Close() {
  [(PWindow *)m_Window close];
}

} // namespace Papaya