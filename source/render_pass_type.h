// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

// Bit position corresponding to each pass. We store in an 
//  int, for each node. This tells us which nodes to render in each pass.
struct render_pass_type
{
  static const unsigned int SHADOW_PASS = 0x0001;
  static const unsigned int SHADOW_ALPHA_PASS = 0x0002;
  static const unsigned int FORWARD_OPAQUE_PASS = 0x004;
  static const unsigned int FORWARD_BLENDED_PASS = 0x008;

  static const unsigned int ALL = 0xffff;
};

