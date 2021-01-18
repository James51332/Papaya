#ifndef Memory_h
#define Memory_h

#include <memory>

namespace Papaya
{

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
  return std::make_unique<T>(std::forward<Args>(args)...);
}

// This is literally a copy of std::move but I just wrapped it.
template<typename T>
constexpr std::remove_reference_t<T>&& Move(T&& t) noexcept {
  return std::move(t);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
  return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Papaya


#endif /* end of include guard: Memory_h */