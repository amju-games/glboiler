#include <iostream>

#include "gl_includes.h" // TODO TEMP TEST

#include "boiler_assert.h"
#include "file.h"
#include "obj_mesh.h"
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

bool ObjMesh::Load(const std::string& filename, bool binary)
{
  //if (binary)
  //{
  //  return LoadBinary(filename);
  //}

  if (ShowInfo())
  {
    std::cout << "Loading file " << filename << " - text, not binary\n";
  }

  text_file f;
  if (!f.open_for_reading(filename))
  {
    return false;
  }

  // Start off with a default group name - using the filename makes
  //  it unique, so we can merge obj files.
  std::string currentGroup = filename;

  // Set name for default group..?
  // Bad idea, as we can end up with an empty group
  // TODO Remove any empty groups
  Group& g = m_groups[currentGroup];
  g.m_name = currentGroup;

  while (true)
  {
    std::string s;
    if (!f.read_string(&s))
    {
      break;
    }
    s = trim(s);
    if (s.empty())
    {
      continue;
    }

    strings strs = split(s, ' ');
    gl_boiler_assert(!strs.empty());

    if (strs[0] == "v")
    {
      m_points.push_back(ToVec3(strs));
    }
    else if (strs[0] == "vn")
    {
      vec3 n = ToVec3(strs);
      n = normalise(n);
      m_normals.push_back(n);
    }
    else if (strs[0] == "vt")
    {
      m_uvs.push_back(ToVec2(strs));
    }
    else if (strs[0] == "f")
    {
      Group& g = m_groups[currentGroup];
      gl_boiler_assert(!g.m_name.empty());

      if (strs.size() > 4)
      {
        f.report_error("Non-triangular face, taking first 3 verts only.");
      }

      Face face = ToFace(strs);
      m_facemap[g.m_name].push_back(face);
    }
    else if (strs[0] == "g")
    {
      // Switch current group - create a new group if it doesn't
      //  already exist in the map.
      if (strs.size() == 1)
      {
        f.report_error("No group name!");
      }
      else if (strs.size() == 2)
      {
        currentGroup = strs[1];
        Group& g = m_groups[currentGroup];
        g.m_name = currentGroup;
      }
      else
      {
        f.report_error("Info: Unexpected format for group: " + s);
        currentGroup = strs[1];
        for (unsigned int a = 2; a < strs.size(); a++)
        {
          currentGroup += strs[a];
        }
        Group& g = m_groups[currentGroup];
        g.m_name = currentGroup;
      }
    }
    else if (strs[0] == "mtllib")
    {
      if (strs.size() != 2)
      {
        f.report_error("Unexpected format for mtllib");
        continue;
      }

      std::string mtlfilename = strs[1];
      MaterialVec mats;
      if (!LoadMtlFile(mtlfilename, &mats))
      {
        f.report_error("Failed to load mtl file " + mtlfilename);
        return false;
      }
      //mat.m_filename = mtlfilename;

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
    else if (strs[0] == "usemtl")
    {
      if (strs.size() != 2)
      {
        f.report_error("Unexpected format for usemtl");
        continue;
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
        currentGroup = matname + "_group"; // OK if group name exists
        Group& g = m_groups[currentGroup];
        g.m_name = currentGroup;
        g.m_materialName = matname;
      }
    }
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

  MungeData();
  return true;
}

const aabb& ObjMesh::GetAABB()
{
  return m_aabb;
}

const aabb& ObjMesh::GetAABB(const std::string& groupname)
{
  Groups::iterator it = m_groups.find(groupname);
  gl_boiler_assert(it != m_groups.end());
  Group& g = it->second;
  return g.m_aabb; 
}

void ObjMesh::MungeData()
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

    m_aabb = m_aabb.union_with(g.m_aabb);

    // Erase empty groups
    if (g.m_tris.empty())
    {
      if (ShowInfo())
      {
        std::cout << "Removing empty group " << g.m_name << "\n";
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

void ObjMesh::use_on_gl_thread()
{
  for (Groups::iterator it = m_groups.begin();
       it != m_groups.end();
       ++it)
  {
      Group& g = it->second;
      g.use_on_gl_thread();
  }
}

void ObjMesh::upload_on_gl_thread()
{
  for (Groups::iterator it = m_groups.begin();
    it != m_groups.end();
    ++it)
  {
    Group& g = it->second;
    g.upload_on_gl_thread();
  }
}

void ObjMesh::destroy_on_gl_thread()
{
  for (Groups::iterator it = m_groups.begin();
    it != m_groups.end();
    ++it)
  {
    Group& g = it->second;
    g.destroy_on_gl_thread();
  }
}

void ObjMesh::reload()
{
  // TODO reload separately from shaders/textures, as could take a long time
}

void ObjMesh::GetMaterials(MaterialVec* vec)
{
  for (Materials::iterator it = m_materials.begin(); it != m_materials.end(); ++it)
  {
    vec->push_back(it->second);
  } 
}

Group* ObjMesh::GetGroup(const std::string& groupName)
{
  Groups::iterator it = m_groups.find(groupName);
  if (it == m_groups.end())
  {
    return 0;
  } 
  return &it->second;
}

void ObjMesh::BuildGroup(Group& g)
{
  // Only need to build Tris once - this kind of mesh is not animated!
  Faces& faces = m_facemap[g.m_name];

  unsigned int numfaces = faces.size();

  if (ShowInfo())
  {
    std::cout << "Group " << g.m_name << " has " << numfaces << " faces.\n";
    if (m_uvs.empty())
    {
      std::cout << "No UVs in this obj mesh!\n";
    }
  }

  g.m_tris.reserve(numfaces);
  for (unsigned int i = 0; i < numfaces; i++)
  {
    const Face& f = faces[i];
    Tri t;
    for (int j = 0; j < 3; j++)
    {
      if (!m_normals.empty())
      {
        unsigned int n = f.m_normalIndex[j];
        gl_boiler_assert(n < m_normals.size());
        const vec3& vN = m_normals[n];

        t.m_verts[j].m_normal = vN;
      }

      if (m_uvs.empty())
      {
        t.m_verts[j].m_uv = vec2(0, 0);
      }
      else
      {
        unsigned int uv = f.m_uvIndex[j];
        gl_boiler_assert(uv < m_uvs.size());
        const vec2& vUV = m_uvs[uv];

        t.m_verts[j].m_uv = vUV;
      }

      gl_boiler_assert(!m_points.empty());

      unsigned int p = f.m_pointIndex[j];
      gl_boiler_assert(p < m_points.size());
      const vec3 vP = m_points[p];

      t.m_verts[j].m_pos = vP;
      m_aabb.set_if(vP);
    }
    g.m_tris.push_back(t);
  }

  if (ShowInfo())
  {
    std::cout << "BuildGroup: " << g.m_tris.size() << " tris in group \"" << g.m_name << "\".\n";
  }

  //g.m_triList = MakeTriList(g.m_tris);
  //if (g.m_triList)
  //{
  //  g.m_triList->CalcTangents(); 
  //}
}

void ObjMesh::DrawGroup(Group& g)
{
  if (!g.IsVisible())
  {
    return;
  }

  // TODO TEMP TEST

  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < g.m_tris.size(); i++)
  {
    const Tri& tri = g.m_tris[i];
    for (int v = 0; v < 3; v++)
    {
      const Vert& vert = tri.m_verts[v];
      glNormal3fv(&vert.m_normal.x);
      glTexCoord2fv(&vert.m_uv.x);
      glVertex3fv(&vert.m_pos.x);
    }
  }
  glEnd();

  //// Material can set lighting/blending flags
  //AmjuGL::PushAttrib(AmjuGL::AMJU_LIGHTING | AmjuGL::AMJU_BLEND);

  //// TODO Hash, not string
  //Materials::iterator it = m_materials.find(g.m_materialName);
  //if (it != m_materials.end())
  //{
  //  Material& mat = it->second;
  //  mat.UseThisMaterial();
  //}

  //AmjuGL::Draw(g.m_triList);

  //AmjuGL::PopAttrib();
}

void ObjMesh::Merge(const ObjMesh& om)
{
  m_materials.insert(om.m_materials.begin(), om.m_materials.end());
  m_groups.insert(om.m_groups.begin(), om.m_groups.end());
}

