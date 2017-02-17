// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
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

size_t binary_file::write_binary(size_t num_bytes, const void* src)
{
  if (!m_file.is_open())
  {
    // No good for tests
    //gl_boiler_stop;
    report_error("File not open");
    return 0;
  }

  m_file.write(static_cast<const char*>(src), num_bytes);
  return num_bytes;
}

size_t binary_file::read_binary(size_t num_bytes, void* dest)
{
  if (!m_file.is_open())
  {
    // No good for tests
    //gl_boiler_stop;
    report_error("File not open");
    return 0;
  }

  if (m_file.eof())
  {
    report_error("End of file");
    return 0;
  }

  m_file.read(static_cast<char*>(dest), num_bytes);
  return static_cast<size_t>(m_file.gcount());
}

bool binary_file::seek(size_t file_pos)
{
  if (!m_file.is_open() || m_file.eof())
  {
    // No good for tests
    //gl_boiler_stop;
    return false;
  }

  m_file.seekg(file_pos);

  return m_file.good();
}

bool binary_file::write_int(int i)
{
  return (write_binary(sizeof(int), &i) == sizeof(int));
}

bool binary_file::read_int(int& i)
{
  return (read_binary(sizeof(int), &i) == sizeof(int));
}

bool binary_file::write_string(const std::string& s)
{
  int n = static_cast<int>(s.size());
  if (!write_int(n))
  {
    report_error("Failed to write string '" + s + "'");
    return false;
  }
  return (write_binary(n, s.c_str()) == n);
}

bool binary_file::read_string(std::string& s)
{
  int n = 0;
  if (!read_int(n))
  {
    return false;
  }
  s.resize(n);
  return (read_binary(n, &s[0]) == n);
}

bool use_binary_file(const std::string& filename)
{
  // Use binary file if the file exists and has a timestamp later (newer) than the text file.
  struct stat text_file_stat_buf;
  bool text_file_exists = (stat(filename.c_str(), &text_file_stat_buf) != -1);

  struct stat binary_file_stat_buf;
  bool binary_file_exists = (stat((filename + ".bin").c_str(), &binary_file_stat_buf) != -1);

  if (binary_file_exists &&
    (!text_file_exists ||
    binary_file_stat_buf.st_mtime > text_file_stat_buf.st_mtime))
  {
    return true;
  }

  return false;
}

