// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "object.h"

class gl_resource : public object
{
public:
  virtual ~gl_resource();

  virtual void upload_on_gl_thread() = 0;
  virtual void use_on_gl_thread() = 0;
  virtual void destroy_on_gl_thread() = 0;

  // Reload from disk - but don't upload on GL thread until upload_on_gl_thread() called
  virtual void reload() = 0;

  bool has_been_uploaded() const { return m_has_been_uploaded; }

protected:
  bool m_destroy_called = false;
  bool m_has_been_uploaded = false;
};

