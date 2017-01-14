// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

// Base class for all types, giving name, serialisation interface, etc.
// TODO ref counted?
class object
{
public:
  virtual ~object() {}

  const std::string& get_name() const;
  void set_name(const std::string& name_);

  // Interface: Serialise as binary
};

