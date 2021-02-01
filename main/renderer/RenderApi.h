#ifndef RenderApi_h
#define RenderApi_h

namespace Papaya
{

// TODO: I don't know if we'll implement all of these but these are just the list of potential candidates
enum class RenderApi
{
  None,
  OpenGL,
  DirectX,
  Metal,
  Vulkan,
};

} // namespace Papaya


#endif /* end of include guard: RenderApi_h */