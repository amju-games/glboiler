#pragma once

#include <map>
#include "obj_material.h"
#include "obj_util.h"
#include "resource.h"

class CollisionMesh;
class Matrix;

class ObjMesh : public gl_resource
{
public:
  virtual void upload_on_gl_thread() override;
  virtual void use_on_gl_thread() override; // draws the VAOs
  virtual void destroy_on_gl_thread() override;

  // Reload from disk - but don't upload on GL thread until upload_on_gl_thread() called
  virtual void reload() override;

  bool Load(const std::string& filename, bool binary = false);
  bool Save(const std::string& filename, bool binary = false);

  // Transform all vertices by the given matrix
  void Transform(const Matrix& m);

  void CalcCollisionMesh(CollisionMesh* pCollMesh) const;

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
  bool LoadBinary(const std::string& filename);
  bool SaveBinary(const std::string& filename);

  // Build groups, clean up temp data etc
  void MungeData();

  // TODO Dump this data once loaded ?
  Vecs m_points;
  Vecs m_normals;
  UVs m_uvs;
  FaceMap m_facemap;

  Groups m_groups;

  typedef std::map<std::string, std::shared_ptr<obj_material>> Materials;
  Materials m_materials;

  aabb m_aabb; // union of all group AABBs

  std::string m_filename;

private:
  void DrawGroup(Group& g);
  void BuildGroup(Group& g);
};

//typedef RCPtr<ObjMesh> PObjMesh;

resource* TextObjLoader(const std::string& resName);
resource* BinaryObjLoader(const std::string& resName);

// Used to load an .obj mesh and other associated files (.mtl and textures)
ObjMesh* LoadObjMesh(const std::string& pathFile, bool binary = false);

