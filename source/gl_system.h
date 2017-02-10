// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

void check_gl_error(const char* statement, const char* filename, int line);

void log_gl_info();

// Call when GL thread is first created. 
void set_gl_thread();

// Checks that the current thread is the GL thread set in set_gl_thread().
void check_gl_thread();

// Set validator function: called as part of GL_CHECK macro, so can be used to 
//  test e.g. matching allocation/deallocation
using gl_validator = void(*)(const char* statement);
void set_validator(gl_validator);

// Calls validator function set above, if one has been set.
void run_validator(const char* statement);

#define GL_CHECK(statement) \
  check_gl_thread(); \
  statement; \
  check_gl_error(#statement, __FILE__, __LINE__); \
  run_validator(#statement);

