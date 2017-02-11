// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include "file.h"

class binary_file : public file
{
public:
  // Virtual functions so we can override in a mocking subclass for testing

  virtual bool open_for_reading(const std::string& filename);

  virtual bool open_for_writing(const std::string& filename);

  virtual size_t read_binary(size_t num_bytes, void* dest);

  virtual size_t write_binary(size_t num_bytes, void* src);

  // Only valid in read mode.
  virtual bool seek(size_t file_pos);

private:
  size_t m_size = 0;
};


