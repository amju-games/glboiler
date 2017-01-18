// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <fstream>
#include <string>

class file
{
public:
  ~file();

  bool open_for_reading(const std::string& filename);

  size_t read_binary(size_t num_bytes, void* dest);

  bool seek(size_t file_pos);

  void close();

  bool read_string(std::string*);

private:
  std::fstream m_file;
  size_t m_size = 0;
};

