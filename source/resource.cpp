// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "boiler_assert.h"
#include "resource.h"

gl_resource::~gl_resource()
{
  if (has_been_uploaded())
  {
    gl_boiler_assert(m_destroy_called);
  }
}

