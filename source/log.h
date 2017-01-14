// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <sstream>

using msg = std::stringstream;
using os = std::basic_ostream<char, std::char_traits<char>>; 

void log(const os&);

void log(const std::string&);

