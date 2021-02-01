#include "CocoaContext.h"

#include "main/core/Log.h"

#include <Cocoa/Cocoa.h>

namespace Papaya
{

////////////////////////////////////////////
///// CocoaContext /////////////////////////
////////////////////////////////////////////

Ref<Context> CocoaContext::Create(RenderApi api)
{
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
    NSOpenGLPFAOpenGLProfile,
    NSOpenGLProfileVersion4_1Core,
    0
  };

  NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc] initWithAttributes: attribs];
  PAPAYA_ASSERT(format, "Failed to create OpenGL Pixel Format!");

  m_Context = [[NSOpenGLContext alloc] initWithFormat: format
                                         shareContext: nil];
  PAPAYA_ASSERT(m_Context, "Failed to create OpenGL Context!");

  m_View = [[NSView alloc] initWithFrame: NSMakeRect(0.0, 0.0, 800.0, 600.0)];
  ((NSView*)m_View).wantsLayer = YES;

  [(NSOpenGLContext*) m_Context setView: (NSView*) m_View];

  [(NSOpenGLContext*) m_Context makeCurrentContext];
  [(NSOpenGLContext*) m_Context flushBuffer];
}

CocoaOpenGLContext::~CocoaOpenGLContext()
{

}

} // namespace Papaya