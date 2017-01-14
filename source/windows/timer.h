// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

#define time_this_block(name) block_timer bt(name);

class block_timer
{
public:
  block_timer(const std::string& name_to_log);
  ~block_timer();

private:
  std::string m_name_to_log;
};

