#pragma once

#include <map>
#include "gl_mesh.h"
#include "obj_material.h"
#include "obj_util.h"

class resource_manager;

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

  static bool ShowInfo();

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

  std::string m_filename;

private:
  //void DrawGroup(Group& g);
  void BuildGroup(Group& g);
};

// Used to load an .obj mesh and other associated files (.mtl and textures)
ObjMesh* LoadObjMesh(const std::string& pathFile, bool binary = false);

