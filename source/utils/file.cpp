// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include <sys/types.h>
#include <sys/stat.h>
#include "boiler_assert.h"
#include "file.h"
#include "log.h"
#include "string_utils.h"

//#define FILE_DEBUG

file::~file()
{
  close();
}

bool file::open(const std::string& filename, std::ios::openmode mode)
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
  else
  {
    log(msg() << "FAILED to open for reading: \"" << filename << "\"");
    gl_boiler_stop;
  }

  return m_file.is_open();
}

bool text_file::open_for_reading(const std::string& filename)
{
  return file::open(filename, std::ios::in);
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

bool text_file::read_string(std::string* s)
{
  if (!m_file.is_open())
  {
    report_error("File not open");
    return false;
  }

  // Skip blank lines... right?
  while (trim(*s).empty())
  {
    if (m_file.eof())
    {
      // Not an error if we are looping like this:
      //  while (f.read_string... 
      return false;
    }

    m_line++;
    std::getline(m_file, *s);
  }

  return true;
}
  
void text_file::report_error(const std::string& err)
{
  if (m_filename.empty())
  {
    log(msg() << "File: no filename: error: " << err);
  }
  else
  {
    log(msg() << "File: " << m_filename << " line: " << m_line << ": error: " << err);
  }
}

void file::close()
{
  m_file.close();
}

bool file_exists(const std::string& filename)
{
  struct stat buf;
  bool exists = (stat(filename.c_str(), &buf) != -1);
  return exists;
}

