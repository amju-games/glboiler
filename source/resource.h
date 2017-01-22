// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

class resource
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
};

