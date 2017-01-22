// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "boiler_assert.h"
#include "file.h"
#include "log.h"
#include "string_utils.h"

//#define FILE_DEBUG

file::~file()
{
  close();
}

bool file::open_for_reading(const std::string& filename, std::ios::openmode mode)
{
  if (m_file.is_open())
  {
    if (filename != m_filename)
    {
      gl_boiler_stop;
    }
    log(msg() << "Already open for reading: \"" << filename << "\"");
    return true;
  }
  m_filename = filename;
  m_file.open(filename, mode);
  if (m_file.is_open())
  {
#ifdef FILE_DEBUG
    log(msg() << "Opening for reading: \"" << filename << "\"");
#endif
    //    m_file.seekg(0, m_file.end);
    //    m_size = m_file.tellg();
    //    m_file.seekg(0, m_file.beg);
  }

  return m_file.is_open();
}

bool text_file::open_for_reading(const std::string& filename)
{
  return file::open_for_reading(filename, std::ios::in);
}

bool binary_file::open_for_reading(const std::string& filename)
{
  return file::open_for_reading(filename, std::ios::in | std::ios::binary);
}

void file::report_error(const std::string& err)
{
  if (m_filename.empty())
  {
    log(msg() << "File: no filename: error: " << err);
  }
  else
  {
    log(msg() << "File: " << m_filename << ": error: " << err);
  }
}

size_t binary_file::read_binary(size_t num_bytes, void* dest)
{
  if (!m_file.is_open())
  {
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

bool text_file::read_string(std::string* s)
{
  if (!m_file.is_open())
  {
    report_error("File not open");
    return false;
  }

  if (m_file.eof())
  {
    // Not an error if we are looping like this:
    //  while (f.read_string... 
    return false;
  }

  std::getline(m_file, *s);
  return true;
}
  
bool binary_file::seek(size_t file_pos)
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

