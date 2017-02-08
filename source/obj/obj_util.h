#ifndef OBJ_USEFUL_FUNCTIONS_H
#define OBJ_USEFUL_FUNCTIONS_H

#include <map>
#include <string>
#include <vector>
#include "aabb.h"
#include "string_utils.h"
#include "vec2.h"
#include "vec3.h"
//#include <TriList.h> // TODO need vao type
//#include <Texture.h>
//#include "Material.h"

// Useful types
// ------------

// Vertex buffer element type
struct Vert
{
  vec3 m_pos;
  vec2 m_uv;
  vec3 m_normal;
  vec3 m_tangent; 
};

struct Tri
{
  Vert m_verts[3];
};

typedef std::vector<Tri> Tris; 

// Face type - assumes all faces are triangles,
//  so is most efficient.
struct Face
{
  Face();

  // only triangles are allowed!
  int m_pointIndex[3];
  int m_normalIndex[3];
  int m_uvIndex[3];
};

typedef std::vector<Face> Faces;
typedef std::map<std::string, Faces> FaceMap;

// Group - has name, material name and collection of faces.
struct Group
{
  Group() : m_visible(true), m_collidable(true) {}

  bool IsVisible() const { return m_visible; }
  bool IsCollidable() const { return m_collidable; }
  void SetVisible(bool visible) { m_visible = visible; }
  void SetCollidable(bool collidable) { m_collidable = collidable; }

  void upload_on_gl_thread();
  void use_on_gl_thread();
  void destroy_on_gl_thread();

  bool m_visible;
  bool m_collidable;
  std::string m_name;
  std::string m_materialName; // TODO int index
  Tris m_tris; 

  aabb m_aabb;

  // VAO
  unsigned int m_vao = 0;
  unsigned int m_vbo = 0;
};

// Group with extra info for saving
struct SaveGroup
{
  Faces m_faces;
};

// Map of group name to group object
typedef std::map<std::string, Group> Groups;

// Other useful typedefs for collections
typedef std::vector<vec3> Vecs;
typedef std::vector<vec2> UVs;


// Useful functions
// ----------------

// Convert a vector of four strings to a Vec3. 
// The zeroth string is ignored. Strings 1, 2 & 3 are
//  asssumed to be floats.
vec3 ToVec3(const strings& strs);

// Convert a vector of three strings to a Vec2. 
// The zeroth string is ignored. Strings 1 & 2 are
//  asssumed to be floats.
vec2 ToVec2(const strings& strs);

// Convert a vector of strings to a Face.
// The zeroth string is ignored. We only use the first 
//  three vertices.
Face ToFace(const strings& fstrs);

#endif

