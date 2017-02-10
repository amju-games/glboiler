// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "vertex.h"

void tri::calc_tangents()
{
  vec3 tan[3];
  vec3 xyz1 = m_verts[1].pos - m_verts[0].pos;
  vec3 xyz2 = m_verts[2].pos - m_verts[0].pos;

  vec2 st1 = m_verts[1].uv - m_verts[0].uv;
  vec2 st2 = m_verts[2].uv - m_verts[0].uv;

  float d = st1.x * st2.y - st2.x * st1.y;
  if (d != 0)
  {
    float r = 1.f / d;
  }
}


  /*
  
  // xyz1 = (x1, y1, z1)
  // xyz2 = (x2, y2, z2)
        float x1 = v2.m_x - v1.m_x;
        float x2 = v3.m_x - v1.m_x;
        float y1 = v2.m_y - v1.m_y;
        float y2 = v3.m_y - v1.m_y;
        float z1 = v2.m_z - v1.m_z;
        float z2 = v3.m_z - v1.m_z;

   // vec2 st1 = (s1, t1) = 
        float s1 = v2.m_u - v1.m_u;
        float t1 = v2.m_v - v1.m_v;

    // vec2 st2 = (s2, t2)
        float s2 = v3.m_u - v1.m_u;
        float t2 = v3.m_v - v1.m_v;

        float denom = (s1 * t2 - s2 * t1);
    // = st1.x * st2.y - st2.x * st1.y

        if (denom == 0)
        {
            continue;
        }
        float r = 1.0F / denom;

        Vec3f sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
            (t2 * z1 - t1 * z2) * r);
        Vec3f tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
            (s1 * z2 - s2 * z1) * r);

        int i = a * 3;
        tan1[i] += sdir;
        tan1[i + 1] += sdir;
        tan1[i + 2] += sdir;

        tan2[i] += tdir;
        tan2[i + 1] += tdir;
        tan2[i + 2] += tdir;


        for (int i = 0; i < 3; i++)
        {
        AmjuGL::Vert& v = tri.m_verts[i];
        const Vec3f n(v.m_nx, v.m_ny, v.m_nz); // = normal[a];
        const Vec3f& t = tan1[a * 3 + i];

        // Gram-Schmidt orthogonalize
        Vec3f tangent = (t - n * DotProduct(n, t));
        tangent.Normalise();

        // Calculate handedness
        //GLfloat w = (n.cross(t).dot(tan2[a]) < 0.0F) ? -1.0F : 1.0F;

        v.m_tanx = tangent.x;
        v.m_tany = tangent.y;
        v.m_tanz = tangent.z;
        // TODO Do we need this? It's supposed to be the handedness
        // v.tangent[3] = w;
        }

  */