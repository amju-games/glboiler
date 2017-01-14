// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "log.h"

template<typename T>
void boiler_assert(T expr, const char* expr_str, const char* file, int line)
{
  if (!expr)
  {
    log(msg() << "ASSERT FAILED: " << expr_str << " in " << file << ": " << line);
  }
}

#define assert(expr) boiler_assert(expr, #expr, __FILE__, __LINE__)
