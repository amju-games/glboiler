// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "file.h"
#include "log.h"
#include "string_utils.h"

file::~file()
{
  close();
}
  
bool file::open_for_reading(const std::string& filename)
{
  if (m_file.is_open())
  {
    log(msg() << "Already open for reading: \"" << filename << "\"");
    return true;
  }
  m_file.open(filename, std::ios::in);
  if (m_file.is_open())
  {
    log(msg() << "Opening for reading: \"" << filename << "\"");

//    m_file.seekg(0, m_file.end);
//    m_size = m_file.tellg();
//    m_file.seekg(0, m_file.beg);
  }

  return m_file.is_open();
}
 
size_t file::read_binary(size_t num_bytes, void* dest)
{
  if (!m_file.is_open() || m_file.eof())
  {
    return 0;
  }

  m_file.read(reinterpret_cast<char*>(dest), num_bytes);
  return static_cast<size_t>(m_file.gcount());
}

bool file::read_string(std::string* s)
{
  if (!m_file.is_open() || m_file.eof())
  {
    return false;
  }

  std::getline(m_file, *s);
  return true;
}
  
bool file::seek(size_t file_pos)
{
  if (!m_file.is_open() || m_file.eof())
  {
    return false;
  }

  m_file.seekg(file_pos);

  return m_file.good();
}

void file::close()
{
  m_file.close();
}

