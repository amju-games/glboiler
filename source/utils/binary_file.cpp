// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "binary_file.h"
#include "boiler_assert.h"

bool binary_file::open_for_reading(const std::string& filename)
{
  return file::open(filename, std::ios::in | std::ios::binary);
}

bool binary_file::open_for_writing(const std::string& filename)
{
  return file::open(filename, std::ios::out | std::ios::binary);
}

size_t binary_file::write_binary(size_t num_bytes, void* src)
{
  if (!m_file.is_open())
  {
    gl_boiler_stop;
    report_error("File not open");
    return 0;
  }

  m_file.write(reinterpret_cast<char*>(src), num_bytes);
  return num_bytes;
}

size_t binary_file::read_binary(size_t num_bytes, void* dest)
{
  if (!m_file.is_open())
  {
    gl_boiler_stop;
    report_error("File not open");
    return 0;
  }

  if (m_file.eof())
  {
    report_error("End of file");
    return 0;
  }

  m_file.read(reinterpret_cast<char*>(dest), num_bytes);
  return static_cast<size_t>(m_file.gcount());
}

bool binary_file::seek(size_t file_pos)
{
  if (!m_file.is_open() || m_file.eof())
  {
    gl_boiler_stop;
    return false;
  }

  m_file.seekg(file_pos);

  return m_file.good();
}


