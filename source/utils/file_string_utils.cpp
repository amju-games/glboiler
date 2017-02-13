// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "file_string_utils.h"

std::string just_path(const std::string& path_and_filename)
{
  std::string ret = path_and_filename;
  size_t f = ret.find_last_of('/');
  if (f != std::string::npos)
  {
    ret = ret.substr(0, f + 1);
  }
  return ret;
}

std::string just_filename(const std::string& path_and_filename)
{
  std::string ret = path_and_filename;
  size_t f = ret.find_last_of('/');
  if (f != std::string::npos)
  {
    ret = ret.substr(f + 1);
  }
  return ret;
}

std::string just_extension(const std::string& path_and_filename)
{
  return "";
}

std::string without_extension(const std::string& path_and_filename)
{
  return "";
}
