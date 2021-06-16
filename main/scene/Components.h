
#include "main/utils/String.h"

#include "main/renderer/Texture.h"

namespace Papaya {

struct TagComponent {
  String Name;

  operator String&() { return Name; }
  operator const String&() const { return Name; }

  TagComponent(const String& name)
    : Name(name) {}
};

} // namespace Papaya