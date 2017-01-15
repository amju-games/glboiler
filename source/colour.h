// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

struct colour
{
  colour() : r(1), g(1), b(1), a(1) {}
  colour(float r_, float g_, float b_, float a_) : 
    r(r_), g(g_), b(b_), a(a_) {}

  float r, g, b, a;
};

inline colour operator*(const colour& c1, const colour& c2)
{
  return colour(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
}

inline bool operator==(const colour& c1, const colour& c2)
{
  return    c1.r == c2.r
         && c1.g == c2.g
         && c1.b == c2.b
         && c1.a == c2.a;
}

