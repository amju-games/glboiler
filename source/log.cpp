// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <iostream>
#include "log.h"

void log(const os& m)
{
  log((dynamic_cast<const std::stringstream&>(m)).str());
}

void log(const std::string& s)
{
  std::cout << s << "\n";
}

