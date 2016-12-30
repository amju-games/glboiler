// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include "log.h"

void log(const msg& m)
{
  log(m.str());
}

void log(const std::string& s)
{
  std::cout << s << "\n";
}

