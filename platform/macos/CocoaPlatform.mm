#include "CocoaPlatform.h"

#include <Cocoa/Cocoa.h>
#include <mach/mach_time.h>

namespace Papaya {

CocoaPlatform::CocoaPlatform() {

}

CocoaPlatform::~CocoaPlatform() {

}

void CocoaPlatform::Init() {
  m_Application = [NSApplication sharedApplication];
  [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];

  // https://github.com/glfw/glfw/blob/master/src/cocoa_time.c
  mach_timebase_info_data_t info;
  mach_timebase_info(&info);

  m_TimerFrequency = (info.denom * 1e9) / info.numer;
  m_TimerOffset = mach_absolute_time();

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

double CocoaPlatform::SysTime() {
  return (mach_absolute_time() - m_TimerOffset) / m_TimerFrequency;
}

} // namespace Papaya