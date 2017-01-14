// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "timer.h"

block_timer::block_timer(const std::string& name_to_log) :
  m_name_to_log(name_to_log)
{
}

block_timer::~block_timer()
{
}

