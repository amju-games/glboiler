#include <iostream> // TODO TEMP TEST
#include "file_string_utils.h"
#include "obj_material.h"
#include "resource_manager.h"
#include "string_utils.h"

bool LoadMtlFile(const std::string& mtlfilename, MaterialVec* mats)
{
  text_file f;
  if (!f.open_for_reading(mtlfilename))
  {
    return false;
  }

  std::string path = just_path(mtlfilename);

  obj_material* current = nullptr;

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

    if (strs[0] == "map_Kd" || strs[0] == "map_Ka" || strs[0] == "map_0")
    {
      // .obj/.mtl files can be dodgy
      if (strs.size() != 2)
      {
        f.report_error("Unexpected format for map_Kd/map_Ka");
        continue;
      }

      gl_boiler_assert(current);
      current->m_texfilename[0] = path + strs[1];
    }
    else if (strs[0].substr(0, 4) == "map_")
    {
      std::string sm = strs[0].substr(4);
      int m = to_int(sm);

      std::cout << "Material: found '" << s << "', that is texture map " << m <<  ", right?\n"; 
      current->m_texfilename[m] = path + strs[1];
    }
    else if (strs[0] == "shader")
    {
      // Assume not in same dir so don't prepend path
      std::cout << "Material: found shader " << strs[1] << "\n";
      current->m_shaderName = strs[1];
    }
    else if (strs[0] == "newmtl")
    {
      if (strs.size() != 2)
      {
        f.report_error("Unexpected format for newmtl");
        continue;
      }

      obj_material* mat = new obj_material;
      mats->push_back(std::shared_ptr<obj_material>(mat));
      current = mat;
      current->m_filename = mtlfilename;
      current->m_name = strs[1];
    }
    else if (strs[0] == "flags")
    {
      if (strs.size() != 2)
      {
        f.report_error("Unexpected format for flags");
        continue;
      }

      gl_boiler_assert(strs.size() == 2);
      current->m_flags = to_int(strs[1]);
    }
  }
  return true;
}

