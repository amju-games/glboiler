// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

#pragma once

#include <string>
#include <vector>
// TODO 
// The maximum amount of textures to load
#define MAX_TEXTURES 100								

#include "texture.h"

  // This is our 3D point class.  This will be used to store the vertices of our model.
  class CVector3 
  {
  public:
    float x, y, z;
  };

  // This is our 2D point class.  This will be used to store the UV coordinates.
  class CVector2 
  {
  public:
    float x, y;
  };

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
    CVector3  *pVerts;			// The object's vertices
    CVector3  *pNormals;		// The object's normals
    CVector2  *pTexVerts;		// The texture's UV coordinates
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

