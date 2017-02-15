#include <iostream>
#include "binary_file.h"
#include "boiler_assert.h"
#include "file.h"
#include "file_string_utils.h"
#include "obj_mesh.h"
#include "resource_manager.h"
#include "mesh_scene_node.h"
#include "string_utils.h"

#ifdef _DEBUG
#define OBJ_DEBUG
#endif

// Empty string for texture and shader names which are not set
#define EMPTY_STRING "$EMPTY$"

bool ObjMesh::ShowInfo()
{
  return true;
}

void ObjMesh::parse_v(const strings& strs, std::string& currentGroup, file& f)
{
  m_points.push_back(ToVec3(strs));
}

void ObjMesh::parse_vn(const strings& strs, std::string& currentGroup, file& f)
{
  vec3 n = ToVec3(strs);
  n = normalise(n);
  m_normals.push_back(n);
}

void ObjMesh::parse_vt(const strings& strs, std::string& currentGroup, file& f)
{
  m_uvs.push_back(ToVec2(strs));
}

void ObjMesh::parse_f(const strings& strs, std::string& currentGroup, file& f)
{
  Group& g = m_groups[currentGroup];
  gl_boiler_assert(!g.get_name().empty());

  if (strs.size() > 4)
  {
    f.report_error("Non-triangular face, taking first 3 verts only.");
  }

  Face face = ToFace(strs);
  m_facemap[g.get_name()].push_back(face);
}

void ObjMesh::parse_g(const strings& strs, std::string& currentGroup, file& f)
{
  // Switch current group - create a new group if it doesn't
  //  already exist in the map.
  if (strs.size() == 1)
  {
    f.report_error("No group name!");
  }
  else if (strs.size() == 2)
  {
    currentGroup = get_name() + strs[1];
    Group& g = m_groups[currentGroup];
    g.set_name(currentGroup);
  }
  else
  {
    f.report_error("Info: Unexpected format for group: g " + strs[1] + " " + strs[2] + "...");
    currentGroup = get_name() + strs[1];
    for (unsigned int a = 2; a < strs.size(); a++)
    {
      currentGroup += strs[a];
    }
    Group& g = m_groups[currentGroup];
    g.set_name(currentGroup);
  }
}

void ObjMesh::parse_mtllib(const strings& strs, std::string& currentGroup, file& f)
{
  if (strs.size() != 2)
  {
    f.report_error("Unexpected format for mtllib");
    return;
  }

  std::string mtlfilename = just_path(m_filename) + strs[1];
  MaterialVec mats;
  if (!LoadMtlFile(mtlfilename, &mats))
  {
    f.report_error("Failed to load mtl file " + mtlfilename);
    return;
  }

  for (unsigned int i = 0; i < mats.size(); i++)
  {
    std::shared_ptr<obj_material> mat = mats[i];

    gl_boiler_assert(!mat->m_name.empty());
    // Only add if texture specified 
    if (!mat->m_texfilename[0].empty())
    {
      m_materials[mat->m_name] = mat;
    }
    else
    {
      if (ShowInfo())
      {
        std::cout << "Discarding material " << mat->m_name << " as no texture\n";
      }
    }
  }
}

void ObjMesh::parse_usemtl(const strings& strs, std::string& currentGroup, file& f)
{
  if (strs.size() != 2)
  {
    f.report_error("Unexpected format for usemtl");
    return;
  }

  std::string matname = strs[1];
  Group& g = m_groups[currentGroup];
  if (g.m_materialName.empty())
  {
    g.m_materialName = matname;
  }
  else
  {
    if (ShowInfo())
    {
      std::cout << "Changing material within the same group - sigh, making new group.\n";
    }

    // Make name for group
    currentGroup = get_name() + matname + "_group"; // OK if group name exists
    Group& g = m_groups[currentGroup];
    g.set_name(currentGroup);
    g.m_materialName = matname;
  }
}

void ObjMesh::parse_line(const std::string& s, std::string& currentGroup, file& f)
{
  strings strs = split(s, ' ');
  gl_boiler_assert(!strs.empty());

  if (strs[0] == "v")
  {
    parse_v(strs, currentGroup, f);
  }
  else if (strs[0] == "vn")
  {
    parse_vn(strs, currentGroup, f);
  }
  else if (strs[0] == "vt")
  {
    parse_vt(strs, currentGroup, f);
  }
  else if (strs[0] == "f")
  {
    parse_f(strs, currentGroup, f);
  }
  else if (strs[0] == "g")
  {
    parse_g(strs, currentGroup, f);
  }
  else if (strs[0] == "mtllib")
  {
    parse_mtllib(strs, currentGroup, f);
  }
  else if (strs[0] == "usemtl")
  {
    parse_usemtl(strs, currentGroup, f);
  }
}

bool ObjMesh::load(const std::string& filename, resource_manager& rm)
{
  std::string bin_filename = filename + ".bin";
  if (use_binary_file(filename))
  {
    return load_binary(bin_filename, rm);
  }
  else
  {
    if (load_text(filename, rm))
    {
      save_binary(bin_filename);
      return true;
    }
  }
  return false;
}

bool ObjMesh::load_binary(const std::string& filename, resource_manager& rm)
{
  binary_file f;
  if (!f.open_for_reading(filename))
  {
    return false;
  }
  int num_groups = 0;
  if (!f.read_int(num_groups))
  {
    return false;
  }
  for (int i = 0; i < num_groups; i++)
  {
    Group g;
    if (!g.load_binary(f))
    {
      return false;
    }
    m_groups[g.get_name()] = g; // hmm
    rm.add_gl_resource(g.get_name(), std::shared_ptr<Group>(new Group(g)));
  }
  int num_materials = 0;
  if (!f.read_int(num_materials))
  {
    return false;
  }
  for (int i = 0; i < num_materials; i++)
  {
    std::string mat_name;
    if (!f.read_string(mat_name))
    {
      return false;
    }
    std::shared_ptr<obj_material> mat(new obj_material);
    if (!mat->load_binary(f))
    {
      return false;
    }
    m_materials[mat_name] = mat;
  }
  return true;
}

bool ObjMesh::save_binary(const std::string& filename)
{
  binary_file f;
  if (!f.open_for_writing(filename))
  {
    return false;
  }
  if (!f.write_int(m_groups.size()))
  {
    return false;
  }
  for (auto& g : m_groups)
  {
    if (!g.second.save_binary(f))
    {
      return false;
    }
  }
  if (!f.write_int(m_materials.size()))
  {
    return false; 
  }
  for (auto& m : m_materials)
  {
    if (!f.write_string(m.first))
    {
      return false;
    }
    if (!m.second->save_binary(f))
    {
      return false;
    }
  }

  return true;
}

bool ObjMesh::load_text(const std::string& filename, resource_manager& rm)
{
  if (ShowInfo())
  {
    std::cout << "Loading file " << filename << " - text, not binary\n";
  }

  text_file f;
  if (!f.open_for_reading(filename))
  {
    return false;
  }
  m_filename = filename;
  set_name(filename);

  // Set name for default group. We can end up with empty groups, which we strip later.
  std::string currentGroup = filename;
  Group& g = m_groups[currentGroup];
  g.set_name(currentGroup);

  while (true)
  {
    std::string s;
    if (!f.read_string(&s))
    {
      break;
    }
    s = trim(s);

    parse_line(s, currentGroup, f);
  }

  if (m_points.empty())
  {
    if (ShowInfo())
    {
      std::cout << "No point data - failed!\n";
    }
    return false;
  }

  if (ShowInfo())
  {
    std::cout << "Points: " << m_points.size()
      << " UVs: " << m_uvs.size() 
      << " Norms: " << m_normals.size()
      << " Groups: " << m_groups.size()
      << " Mats: " << m_materials.size()
      << "\n";
  }

  MungeData(rm);
  return true;
}

void ObjMesh::MungeData(resource_manager& rm)
{
  if (ShowInfo())
  {
    std::cout << "Optimising .obj data...\n";
  }

  for (Groups::iterator it = m_groups.begin();
    it != m_groups.end();
    /* increment in body */)
  {
    Group& g = it->second;
    BuildGroup(g);

    // Erase empty groups
    if (g.m_tris.empty())
    {
      if (ShowInfo())
      {
        std::cout << "Removing empty group " << g.get_name() << "\n";
      }

#ifdef WIN32
      it = m_groups.erase(it);
#else
      auto jt = it;
      ++jt;
      m_groups.erase(it);
      it = jt;
#endif
    }
    else
    {
      // Add group to resource manager
      std::string name = g.get_name(); 
      rm.add_gl_resource(name, std::shared_ptr<Group>(new Group(g)));
      ++it;
    }
  }

  // Remove unused materials
  for (Materials::iterator it = m_materials.begin(); it != m_materials.end(); )
  {
    bool found = false;
    std::string matName = it->first;
    // Look for this name in all groups
    for (Groups::iterator jt = m_groups.begin(); jt != m_groups.end(); ++jt)
    {
      const Group& g = jt->second;
      if (g.m_materialName == matName)
      {
        found = true;
        break;
      }
    }
    if (found)
    {
      if (ShowInfo())
      {
        std::cout << "KEEPING material " << matName << "\n";
      }
      ++it;
    }
    else
    {
      if (ShowInfo())
      {
        std::cout << "Removing unused material " << matName << "\n";
      }

      it = m_materials.erase(it);
    }
  }

  // Remove data no longer needed (only used to create group data)
  m_points.clear();
  m_normals.clear();
  m_uvs.clear();
  m_facemap.clear();

  if (ShowInfo())
  {
    std::cout << "MungeData finished.\n";
  }
}

std::vector<std::shared_ptr<scene_node>> ObjMesh::make_scene_nodes(resource_manager& rm)
{
  std::vector<std::shared_ptr<scene_node>> ret;
  for (auto& p : m_groups)
  {
    std::shared_ptr<mesh_scene_node> n(new mesh_scene_node);
    ret.push_back(n);
    // Get group from res manager
    Group& g = p.second;
    std::string name = g.get_name();
    n->set_name("Mesh_node_for_" + name);
    auto mesh = rm.get_resource(name);
    n->set_mesh(mesh); 

    if (m_materials[g.m_materialName])
    {
      obj_material& om = *m_materials[g.m_materialName].get();
      std::shared_ptr<material> mat(new material);
      if (!om.m_shaderName.empty())
      {
        auto sh = rm.get_shader(om.m_shaderName);
        mat->set_shader(sh);
      }
      for (int i = 0; i < obj_material::MAX_TEXTURES; i++)
      {
        if (!om.m_texfilename[i].empty())
        {
          auto tex = rm.get_texture(om.m_texfilename[i]);
          mat->set_texture(tex);
        }
      }
      n->set_material(mat);
    }

  }
  return ret;
}

void ObjMesh::reload()
{
  // TODO reload separately from shaders/textures, as could take a long time
}

void ObjMesh::BuildGroup(Group& g)
{
  // Only need to build Tris once - this kind of mesh is not animated!
  Faces& faces = m_facemap[g.get_name()];

  unsigned int numfaces = faces.size();

  if (ShowInfo())
  {
    std::cout << "Group " << g.get_name() << " has " << numfaces << " faces.\n";
    if (m_uvs.empty())
    {
      std::cout << "No UVs in this obj mesh!\n";
    }
  }

  g.m_tris.reserve(numfaces);
  for (unsigned int i = 0; i < numfaces; i++)
  {
    const Face& f = faces[i];
    tri t;
    for (int j = 0; j < 3; j++)
    {
      if (!m_normals.empty())
      {
        unsigned int n = f.m_normalIndex[j];
        gl_boiler_assert(n < m_normals.size());
        const vec3& vN = m_normals[n];

        // 2 - j to match winding order elsewhere - TODO change back?
        t.m_verts[2 - j].normal = vN;
      }

      if (m_uvs.empty())
      {
        t.m_verts[2 - j].uv = vec2(0, 0);
      }
      else
      {
        unsigned int uv = f.m_uvIndex[j];
        gl_boiler_assert(uv < m_uvs.size());
        const vec2& vUV = m_uvs[uv];

        t.m_verts[2 - j].uv = vUV;
      }

      gl_boiler_assert(!m_points.empty());

      unsigned int p = f.m_pointIndex[j];
      gl_boiler_assert(p < m_points.size());
      const vec3 vP = m_points[p];

      t.m_verts[2 - j].pos = vP;
    }
    t.calc_tangents();
    g.m_tris.push_back(t);
  }

  if (ShowInfo())
  {
    std::cout << "BuildGroup: " << g.m_tris.size() << " tris in group \"" << g.get_name() << "\".\n";
  }
}

