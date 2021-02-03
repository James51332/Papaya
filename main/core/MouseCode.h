#ifndef MouseCode_h
#define MouseCode_h

namespace Papaya
{

enum MouseCode
{
  MouseNone = 0,
  MouseLeft,
  MouseRight,
  MouseMiddle,
  Mouse4,
  Mouse5,
  Mouse6,
  Mouse7,
  Mouse8,
  Mouse9,
  Mouse10,
  Mouse11,
  Mouse12,
  Mouse13 // TODO: I just added 10 non-main mouse codes. In retrospect, we definitely don't need this many.
};

#define PAPAYA_TOTAL_MOUSECODES 13

} // namespace Papaya


#endif /* end of include guard: MouseCode_h */