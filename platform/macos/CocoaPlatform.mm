#include "CocoaPlatform.h"

#include <Cocoa/Cocoa.h>

namespace Papaya {

CocoaPlatform::CocoaPlatform() {

}

CocoaPlatform::~CocoaPlatform() {

}

void CocoaPlatform::Init() {
  m_Application = [NSApplication sharedApplication];
  [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];

  //TODO: Create Menubar
}

void CocoaPlatform::Update() {
  for (;;) {
    NSEvent* event = [NSApp nextEventMatchingMask: NSEventMaskAny
                                                untilDate: [NSDate distantPast]
                                                   inMode: NSDefaultRunLoopMode
                                                  dequeue: YES];

    if (!event)
      break;
    else
      [NSApp sendEvent: event];
  } 
}

void CocoaPlatform::Terminate() {
  [NSApp terminate: nil];
}

} // namespace Papaya