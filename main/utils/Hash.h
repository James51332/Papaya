#ifndef Hash_h
#define Hash_h

namespace Papaya
{

  // http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
  template <typename T>
  void HashCombine(std::size_t &Seed, const T &Val)
  {
    Seed ^= std::hash<T>()(Val) + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
  }

} // namespace Papaya

#endif /* end of include guard: Hash_h */