// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

// Zero-based number for each pass. We store as bit positions in an 
//  int, for each node. This tells us which nodes to render in each pass.
enum class render_pass_type
{
  SHADOW_PASS,
  SHADOW_ALPHA_PASS,
  FORWARD_OPAQUE_PASS,
  FORWARD_BLENDED_PASS,

  ALL
};

