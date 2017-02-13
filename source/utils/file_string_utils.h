// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>

std::string just_path(const std::string& path_and_filename);

std::string just_filename(const std::string& path_and_filename);

std::string just_extension(const std::string& path_and_filename);

std::string without_extension(const std::string& path_and_filename);
