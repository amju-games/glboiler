// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

void check_gl_error(const char* statement, const char* filename, int line);

#define GL_CHECK(statement) \
  statement; check_gl_error(#statement, __FILE__, __LINE__); 

void log_gl_info();

