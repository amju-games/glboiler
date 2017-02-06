// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

// Base class for all types, giving name, serialisation interface, etc.
// TODO ref counted? No, as we are using std::shared_ptr.
class object
{
public:
  virtual ~object() {}

  const std::string& get_name() const { return m_name; }
  void set_name(const std::string& name_) { m_name = name_; }

  // Interface: Serialise as binary

protected:
  std::string m_name;
};

