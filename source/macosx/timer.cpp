// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "timer.h"
#include "log.h"

static timeval time_now()
{
  timeval tv;
  gettimeofday(&tv, 0);
  return tv;
}

block_timer::block_timer(const std::string& name_to_log) :
  m_name_to_log(name_to_log),
  m_tv(time_now())
{
}

block_timer::~block_timer()
{
  timeval tv = time_now();
  double diff = tv.tv_sec - m_tv.tv_sec + (tv.tv_usec - m_tv.tv_usec) * 1e-6;

  log(msg() << "TIMER: # " << m_name_to_log << " # : " << diff * 1000.0 << "ms");
}

