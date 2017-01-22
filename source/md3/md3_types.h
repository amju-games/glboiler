// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

// Modified from www.gametutorials.com, original author Ben Humphrey, digiben@gametutorials.com

#pragma once

#include <string>
#include <vector>
#include "vec2.h"
#include "vec3.h"

// TODO 
// The maximum amount of textures to load
#define MAX_TEXTURES 100								

#include "texture.h"

// This is our face structure.  This is used for indexing into the vertex 
// and texture coordinate arrays.  From this information we know which vertices
// from our vertex array go to which face, along with the correct texture coordinates.
struct tFace
{
  int vertIndex[3];			// indicies for the verts that make up this triangle
  int coordIndex[3];			// indicies for the tex coords to texture this face

};

// This holds the information for a material.  It may be a texture map of a color.
// Some of these are not used, but I left them.
struct tMaterialInfo
{
  char  strName[255];			// The texture name
  char  strFile[255];			// The texture file name (If this is set it's a texture map)
  unsigned char /* BYTE */   color[3];				// The color of the object (R, G, B)
  texture*   textureId;				// the texture ID
  float uTile;				// u tiling of texture  
  float vTile;				// v tiling of texture	
  float uOffset;			    // u offset of texture
  float vOffset;				// v offset of texture

};

// This holds all the information for our model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject
{
  int  numOfVerts;			// The number of verts in the model
  int  numOfFaces;			// The number of faces in the model
  int  numTexVertex;			// The number of texture coordinates
  int  materialID;			// The texture ID to use, which is the index into our texture array
  bool bHasTexture;			// This is TRUE if there is a texture map for this object
  char strName[255];			// The name of the object
  vec3  *pVerts;			// The object's vertices
  vec3  *pNormals;		// The object's normals
  vec2  *pTexVerts;		// The texture's UV coordinates
  tFace *pFaces;				// The faces information of the object
};

// This holds our information for each animation of the Quake model.
// A STL vector list of this structure is created in our t3DModel structure below.
struct tAnimationInfo
{
  char strName[255];			// This stores the name of the animation (I.E. "TORSO_STAND")
  int startFrame;				// This stores the first frame number for this animation
  int endFrame;				// This stores the last frame number for this animation
  int loopingFrames;			// This stores the looping frames for this animation (not used)
  int framesPerSecond;		// This stores the frames per second that this animation runs

};

// This our model structure
struct t3DModel
{
  int numOfObjects;					// The number of objects in the model
  int numOfMaterials;					// The number of materials for the model
  std::vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
  std::vector<t3DObject> pObject;			// The object list for our model

  int numOfAnimations;				// The number of animations in this model 
  int currentAnim;					// The current index into pAnimations list 
  int currentFrame;					// The current frame of the current animation 
  int nextFrame;						// The next frame of animation to interpolate too
  float t;							// The ratio of 0.0f to 1.0f between each key frame
  float lastTime;						// This stores the last time that was stored
  std::vector<tAnimationInfo> pAnimations; // The list of animations

  int numOfTags;						// This stores the number of tags in the model
  t3DModel			**pLinks;		// This stores a list of pointers that are linked to this model
  struct tMd3Tag		*pTags;			// This stores all the tags for the model animations
};

#define kLower	0			// This stores the ID for the legs model
#define kUpper	1			// This stores the ID for the torso model
#define kHead	2			// This stores the ID for the head model
#define kWeapon	3			// This stores the ID for the weapon model

typedef enum
{
  // If one model is set to one of the BOTH_* animations, the other one should be too,
  // otherwise it looks really bad and confusing.

  BOTH_DEATH1 = 0,		// The first twirling death animation
  BOTH_DEAD1,				// The end of the first twirling death animation
  BOTH_DEATH2,			// The second twirling death animation
  BOTH_DEAD2,				// The end of the second twirling death animation
  BOTH_DEATH3,			// The back flip death animation
  BOTH_DEAD3,				// The end of the back flip death animation

  // The next block is the animations that the upper body performs

  TORSO_GESTURE,			// The torso's gesturing animation

  TORSO_ATTACK,			// The torso's attack1 animation
  TORSO_ATTACK2,			// The torso's attack2 animation

  TORSO_DROP,				// The torso's weapon drop animation
  TORSO_RAISE,			// The torso's weapon pickup animation

  TORSO_STAND,			// The torso's idle stand animation
  TORSO_STAND2,			// The torso's idle stand2 animation

  // The final block is the animations that the legs perform

  LEGS_WALKCR,			// The legs's crouching walk animation
  LEGS_WALK,				// The legs's walk animation
  LEGS_RUN,				// The legs's run animation
  LEGS_BACK,				// The legs's running backwards animation
  LEGS_SWIM,				// The legs's swimming animation

  LEGS_JUMP,				// The legs's jumping animation
  LEGS_LAND,				// The legs's landing animation

  LEGS_JUMPB,				// The legs's jumping back animation
  LEGS_LANDB,				// The legs's landing back animation

  LEGS_IDLE,				// The legs's idle stand animation
  LEGS_IDLECR,			// The legs's idle crouching animation

  LEGS_TURN,				// The legs's turn animation

  MAX_ANIMATIONS			// The define for the maximum amount of animations
} eAnimations;

// This holds the header information that is read in at the beginning of the file
struct tMd3Header
{
  char	fileID[4];					// This stores the file ID - Must be "IDP3"
  int		version;					// This stores the file version - Must be 15
  char	strFile[68];				// This stores the name of the file
  int		numFrames;					// This stores the number of animation frames
  int		numTags;					// This stores the tag count
  int		numMeshes;					// This stores the number of sub-objects in the mesh
  int		numMaxSkins;				// This stores the number of skins for the mesh
  int		headerSize;					// This stores the mesh header size
  int		tagStart;					// This stores the offset into the file for tags
  int		tagEnd;						// This stores the end offset into the file for tags
  int		fileSize;					// This stores the file size

  friend std::ostream& operator<<(std::ostream& os, const tMd3Header& h)
  {
    os << "HEADER: \n" << h.fileID[0] << h.fileID[1] << h.fileID[2] << h.fileID[3] << "\n"
      << "Ver: " << h.version << "\n"
      << "str file: " << h.strFile << "\n"
      << "numFrames: " << h.numFrames << "\n"
      << "numTags: " << h.numTags << "\n"
      << "numMeshes: " << h.numMeshes << "\n"
      << "numMaxSkins: " << h.numMaxSkins << "\n"
      << "headerSize: " << h.headerSize << "\n"
      << "tagStart: " << h.tagStart << "\n"
      << "tagEnd: " << h.tagEnd << "\n"
      << "fileSize: " << h.fileSize << "\n";
    return os;
  }
};

// This structure is used to read in the mesh data for the .md3 models
struct tMd3MeshInfo
{
  char	meshID[4];					// This stores the mesh ID (We don't care)
  char	strName[68];				// This stores the mesh name (We do care)
  int		numMeshFrames;				// This stores the mesh aniamtion frame count
  int		numSkins;					// This stores the mesh skin count
  int     numVertices;				// This stores the mesh vertex count
  int		numTriangles;				// This stores the mesh face count
  int		triStart;					// This stores the starting offset for the triangles
  int		headerSize;					// This stores the header size for the mesh
  int     uvStart;					// This stores the starting offset for the UV coordinates
  int		vertexStart;				// This stores the starting offset for the vertex indices
  int		meshSize;					// This stores the total mesh size

};

// This is our tag structure for the .MD3 file format.  These are used link other
// models to and the rotate and transate the child models of that model.
struct tMd3Tag
{
  char		strName[64];			// This stores the name of the tag (I.E. "tag_torso")
  vec3	vPosition;				// This stores the translation that should be performed
  float		rotation[3][3];			// This stores the 3x3 rotation matrix for this frame

};

// This stores the bone information (useless as far as I can see...)
struct tMd3Bone
{
  float	mins[3];					// This is the min (x, y, z) value for the bone
  float	maxs[3];					// This is the max (x, y, z) value for the bone
  float	position[3];				// This supposedly stores the bone position???
  float	scale;						// This stores the scale of the bone
  char	creator[16];				// The modeler used to create the model (I.E. "3DS Max")

};

// This stores the normals and vertex indices 
struct tMd3Triangle
{
  signed short	 vertex[3];				// The vertex for this face (scale down by 64.0f)
  unsigned char normal[2];				// This stores some crazy normal values (not sure...)

  vec3 decodedNormal() const
  {
    // j.c. - from https://www.icculus.org/homepages/phaethon/q3a/formats/md3format.html
    const float f = static_cast<float>(2.0 * M_PI) / 255.f;
    float lat = static_cast<float>(normal[1]) * f;
    float lng = static_cast<float>(normal[0]) * f;
    return vec3(cos(lat) * sin(lng), sin(lat) * sin(lng), cos(lng));
  }
};

// This stores the indices into the vertex and texture coordinate arrays
struct tMd3Face
{
  int vertexIndices[3];
};

// This stores UV coordinates
struct tMd3TexCoord
{
  float textureCoord[2];
};

// This stores a skin name (We don't use this, just the name of the model to get the texture)
struct tMd3Skin
{
  char strName[68];
};

