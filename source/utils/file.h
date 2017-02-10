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

protected:
  file() = default;
  bool open_for_reading(const std::string& filename, std::ios::openmode mode);
  virtual void report_error(const std::string&);

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

class binary_file : public file
{
public:
  bool open_for_reading(const std::string& filename);
  size_t read_binary(size_t num_bytes, void* dest);
  bool seek(size_t file_pos);

private:
  size_t m_size = 0;
};


