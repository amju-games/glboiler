// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>

using strings = std::vector<std::string>;

// Split string s into multiple strings. Split char is not included in
//  the results. If yes_trim, remove whitespace from beginning and end
//  of result strings.
strings split(const std::string& s, char split_char, bool yes_trim = true);

// Remove whitespace from beginning and end of s
std::string trim(const std::string& s);

std::string replace(
  const std::string& in_this_string, 
  const std::string& replace_this, 
  const std::string& with_this);

bool contains(const std::string& container, const std::string& search_for_this);

int to_int(const std::string& s);

float to_float(const std::string& s);

