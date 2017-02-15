#pragma once

#include <memory>
#include <string>
#include <vector>

// TODO Cubemaps
//#include <Cubemap.h>

#include "binary_file.h"

// * obj_material *
// Describes a material loaded from a .mtl file, as part of loading an .obj mesh.
// This is used to set up a * material * object.
struct obj_material 
{
  bool save_binary(binary_file& f);
  bool load_binary(binary_file& f);

  std::string m_name;
  std::string m_filename;

  // Textures:
  // In the .mtl file, we allow "map_Kd", "map_Ka" and "map_0" for texture[0].
  // Other textures use map_<n>, where n is [1..MAX_TEXTURES)
  enum { MAX_TEXTURES = 8 };
  std::string m_texfilename[MAX_TEXTURES];

  // Cubemap: 6 texture names, using "cube_<n>" n=[0..6) in the .mtl file.
  // Same order as in Cubemap.h, 
  // +x (right)
  // -x (left)
  // +z (front)
  // -z (back)
  // +y (top)
  // -y (bottom)
  std::string m_cubefilename[6];

  // Name of shader, passed to AmjuGL::LoadShader
  // In .mtl file, use "shader"
  std::string m_shaderName;

  unsigned int m_flags = 0;
  // Flags comprised of these values
  enum
  {
    AMJU_MATERIAL_NO_COLLIDE         = 0x01, // 1 to ignore group in collision tests
    AMJU_MATERIAL_SPHERE_MAP         = 0x02, // 1 for sphere mapped
    AMJU_MATERIAL_USE_BLEND_FLAG     = 0x04, // if 1, use next flag
    AMJU_MATERIAL_BLEND_ENABLED      = 0x08, //  ..to enable/disable blending
    AMJU_MATERIAL_USE_LIGHTING_FLAG  = 0x10, // if 1, use next flag
    AMJU_MATERIAL_LIGHTING_ENABLED   = 0x20, //  ..to enable/disable lighting
  };
};

typedef std::vector<std::shared_ptr<obj_material>> MaterialVec;

// Load one mtl file, creating one or more obj_materials. These are then
//  used to make materials. Right? OR just make materials directly? Better to have an intermediate step
//  so we can add texture names etc to res manager?
bool LoadMtlFile(const std::string& mtlfilename, MaterialVec* mats);

