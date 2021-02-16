#ifndef Timestep_h
#define Timestep_h

namespace Papaya
{

class Timestep
{
public:
  Timestep(double time = 0.0f)
    : m_Time(time) {}

  double GetSeconds() const { return m_Time; }
  operator double() const { return m_Time; }

private:
  double m_Time; // measured in seconds
};

} // namespace Papaya


#endif /* end of include guard: Timestep_h */