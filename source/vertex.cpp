// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#include "vertex.h"

void tri::calc_tangents()
{
	vec3 tan1[3];
	vec3 tan2[3];

	const vec3& v1 = m_verts[0].pos;
	const vec3& v2 = m_verts[1].pos;
	const vec3& v3 = m_verts[2].pos;

	// xyz1 = (x1, y1, z1)
	// xyz2 = (x2, y2, z2)
	float x1 = v2.x - v1.x;
	float x2 = v3.x - v1.x;
	float y1 = v2.y - v1.y;
	float y2 = v3.y - v1.y;
	float z1 = v2.z - v1.z;
	float z2 = v3.z - v1.z;

	// vec2 st1 = (s1, t1) = 
	//float s1 = v2.u - v1.u;
	//float t1 = v2.v - v1.v;
	float s1 = m_verts[1].uv.x - m_verts[0].uv.x;
	float t1 = m_verts[1].uv.y - m_verts[0].uv.y;

	// vec2 st2 = (s2, t2)
	//float s2 = v3.u - v1.u;
	//float t2 = v3.v - v1.v;
	float s2 = m_verts[2].uv.x - m_verts[0].uv.x;
	float t2 = m_verts[2].uv.y - m_verts[0].uv.y;

	float denom = (s1 * t2 - s2 * t1);
	// = st1.x * st2.y - st2.x * st1.y

	if (denom == 0)
	{
		return;
	}

	float r = 1.0f / denom;

	vec3 sdir(
		(t2 * x1 - t1 * x2) * r, 
		(t2 * y1 - t1 * y2) * r,
		(t2 * z1 - t1 * z2) * r);

	vec3 tdir(
		(s1 * x2 - s2 * x1) * r, 
		(s1 * y2 - s2 * y1) * r,
		(s1 * z2 - s2 * z1) * r);

	//int i = 0; //a * 3;
	tan1[0] = tan1[0] + sdir;
	tan1[1] = tan1[1] + sdir;
	tan1[2] = tan1[2] + sdir;

	tan2[0] = tan2[0] + tdir;
	tan2[1] = tan2[1] + tdir;
	tan2[2] = tan2[2] + tdir;


	for (int i = 0; i < 3; i++)
	{
		vertex& v = m_verts[i];
		const vec3& n(v.normal);
		const vec3& t = tan1[i];

		// Gram-Schmidt orthogonalize
		vec3 tangent = (t - n * dot(n, t));
		tangent = normalise(tangent);

		// Calculate handedness
		float w = (dot(cross(n, t), tan2[0]) < 0.f) ? -1.f : 1.f;

		v.tangent = tangent * w;
		// TODO Do we need this? It's supposed to be the handedness
		// v.tangent[3] = w;
	}
}

