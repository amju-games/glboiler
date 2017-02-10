// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"

class resource : public object
{
public:
  virtual ~resource() {}
};

class gl_resource : public resource
{
public:
  virtual void upload_on_gl_thread() = 0;
  virtual void use_on_gl_thread() = 0;
  virtual void destroy_on_gl_thread() = 0;

  // Reload from disk - but don't upload on GL thread until upload_on_gl_thread() called
  virtual void reload() = 0;
};

