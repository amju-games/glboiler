// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "log.h"

template<typename T>
void boiler_assert_(T expr, const char* expr_str, const char* file, int line)
{
  if (!expr)
  {
    log(msg() << "ASSERT FAILED: " << expr_str << " in " << file << ": " << line);

    _CrtDbgBreak(); // windows only
  }
}

#ifndef gl_boiler_stop
#define gl_boiler_stop    boiler_assert_(false, "Stopped.", __FILE__, __LINE__)
#endif

#ifndef gl_boiler_assert
#define gl_boiler_assert(expr)    boiler_assert_(expr, #expr, __FILE__, __LINE__)
#endif
