// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#ifdef MACOSX
#include <cassert> // TODO TEMP TEST
#endif

#include "log.h"

template<typename T>
void boiler_assert_(T expr, const char* expr_str, const char* file, int line)
{
  if (!expr)
  {
    log(msg() << "ASSERT FAILED: " << expr_str << " in " << file << ": " << line);

#ifdef WIN32
    _CrtDbgBreak(); // windows only
#endif

#ifdef MACOSX
    assert(0);
#endif
  }
}

#ifndef gl_boiler_stop
#define gl_boiler_stop    boiler_assert_(false, "Stopped.", __FILE__, __LINE__)
#endif

#ifndef gl_boiler_assert
#define gl_boiler_assert(expr)    boiler_assert_(expr, #expr, __FILE__, __LINE__)
#endif
