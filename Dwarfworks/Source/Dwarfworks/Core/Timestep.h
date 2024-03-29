#ifndef CORE_TIME_STEP_H
#define CORE_TIME_STEP_H

namespace Dwarfworks
{
// Time is set as seconds by default, at least for now.
// May consider changing it to 'ms' by default in the future.
class Timestep
{
  public:
    Timestep(float time = 0.0f) : m_Time(time) {}

    // implicit cast to float
    operator float() const { return m_Time; }

    float GetSecnods() const { return m_Time; }
    float GetMilliseconds() const { return m_Time * 1000.0f; }

  private:
    float m_Time;
};

} // namespace Dwarfworks

#endif // CORE_TIME_STEP_H
