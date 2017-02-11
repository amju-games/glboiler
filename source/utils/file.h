// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <fstream>
#include <string>

class file
{
public:
  virtual ~file();

  void close();

  virtual void report_error(const std::string&);

protected:
  file() = default;
  bool open(const std::string& filename, std::ios::openmode mode);

protected:
  std::fstream m_file;
  std::string m_filename;
};

class text_file : public file
{
public:
  bool open_for_reading(const std::string& filename);
  bool read_string(std::string*);
  virtual void report_error(const std::string&) override;

private:
  int m_line;
};

bool file_exists(const std::string& filename);


