#pragma once

#include <map>
#include "gl_mesh.h"
#include "obj_material.h"
#include "obj_util.h"

class resource_manager;

//class CollisionMesh;
//class Matrix;

// Loads an obj mesh. Adds non-empty groups to resource manager, to be added
//  as mesh nodes
class ObjMesh : public gl_mesh
{
public:
  virtual void upload_on_gl_thread() override {}
  virtual void use_on_gl_thread() override {}
  virtual void destroy_on_gl_thread() override {}

  // Reload from disk - but don't upload on GL thread until upload_on_gl_thread() called
  virtual void reload() override;

  virtual std::vector<std::shared_ptr<scene_node>> make_scene_nodes(resource_manager& rm) override;

  bool load(const std::string& filename, resource_manager& rm);

////  bool Save(const std::string& filename, bool binary = false);

  // Transform all vertices by the given matrix
  //void Transform(const Matrix& m);

  //void CalcCollisionMesh(CollisionMesh* pCollMesh) const;

  // Add groups in om to collection of groups in this mesh
  void Merge(const ObjMesh& om);

  // Get group - so special group names can be used for game-related data.
  // (Do we need to get vec of group names ?)
  Group* GetGroup(const std::string& groupName);

  void GetMaterials(MaterialVec* vec);

  const aabb& GetAABB(); // for entire mesh
  const aabb& GetAABB(const std::string& groupname); // for one group

  static void SetShowInfo(bool);
  static bool ShowInfo();

  // Set flag to fail if we can't load textures specified in materials
  static void SetRequireTextures(bool);
  static bool RequiresTextures();

private:
  bool load_text(const std::string& filename, resource_manager& rm);
  bool load_binary(const std::string& filename, resource_manager& rm);

  bool save_binary(const std::string& filename);

  // Build groups, clean up temp data etc
  void MungeData(resource_manager& rm);

  // Parse given line in file f (passed in for error reporting), which may associate 
  //  new data with the current group, or change the current group.
  void parse_line(const std::string& line, std::string& currentGroup, file& f);

  // Parse lines beginning "v", "vn", etc.
  void parse_v(const strings& strs, std::string& currentGroup, file& f);
  void parse_vn(const strings& strs, std::string& currentGroup, file& f);
  void parse_vt(const strings& strs, std::string& currentGroup, file& f);
  void parse_f(const strings& strs, std::string& currentGroup, file& f);
  void parse_g(const strings& strs, std::string& currentGroup, file& f);
  void parse_mtllib(const strings& strs, std::string& currentGroup, file& f);
  void parse_usemtl(const strings& strs, std::string& currentGroup, file& f);
  
  // Data loaded as we parse file. Dumped once vertex buffer(s) built.
  Vecs m_points;
  Vecs m_normals;
  UVs m_uvs;
  FaceMap m_facemap;

  // Temp groups, created as we load.
  Groups m_groups;

  typedef std::map<std::string, std::shared_ptr<obj_material>> Materials;
  Materials m_materials;

  aabb m_aabb; // union of all group AABBs

  std::string m_filename;

private:
  void DrawGroup(Group& g);
  void BuildGroup(Group& g);
};

// Used to load an .obj mesh and other associated files (.mtl and textures)
ObjMesh* LoadObjMesh(const std::string& pathFile, bool binary = false);

// Return true if the binary version of the given filename exists,
//  and it has a timestamp later (newer) than the text file.
// The binary version of a filename has ".bin" appended.
bool use_binary_file(const std::string& filename);

