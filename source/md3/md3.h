// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

// Modified from www.gametutorials.com, original author Ben Humphrey, digiben@gametutorials.com

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "file.h"
#include "md3_types.h"
#include "quat.h"
#include "resource_manager.h"

// This class handles all of the main loading code
class CLoadMD3
{
public:
  CLoadMD3();

  // This is the function that you call to load the MD3 model
  bool ImportMD3(t3DModel *pModel, const std::string& strFileName);

  // This loads a model's .skin file
  bool LoadSkin(t3DModel *pModel, const std::string& strSkin);

  // This loads a weapon's .shader file
  bool LoadShader(t3DModel *pModel, const std::string& strShader);

private:
  // This reads in the data from the MD3 file and stores it in the member variables,
  // later to be converted to our cool structures so we don't depend on Quake3 stuff.
  void ReadMD3Data(t3DModel *pModel);

  // This converts the member variables to our pModel structure, and takes the model
  // to be loaded and the mesh header to get the mesh info.
  void ConvertDataStructures(t3DModel *pModel, tMd3MeshInfo meshHeader);

  // This frees memory and closes the file
  void CleanUp();

  // Member Variables		

  // The file pointer
  binary_file* m_pFile;

  unsigned int m_bytesRead; // bytes read so far from above file

  tMd3Header				m_Header;			// The header data

  tMd3Skin				*m_pSkins;			// The skin name data (not used)
  tMd3TexCoord			*m_pTexCoords;		// The texture coordinates
  tMd3Face				*m_pTriangles;		// Face/Triangle data
  tMd3Triangle			*m_pVertices;		// Vertex/UV indices
  tMd3Bone				*m_pBones;			// This stores the bone data (not used)
};

// This is our model class that we use to load and draw and free the Quake3 characters
class CModelMD3
{
public:
  CModelMD3();
  ~CModelMD3();

  // This loads the model from a path and name prefix.   It takes the path and
  // model name prefix to be added to _upper.md3, _lower.md3 or _head.md3.
  bool LoadModel(const std::string& strPath, resource_manager& rm); 

  // This loads the weapon and takes the same path and model name to be added to .md3
  bool LoadWeapon(const std::string& strPath, const std::string& strModel, resource_manager& rm);

  // This links a model to another model (pLink) so that it's the parent of that child.
  // The strTagName is the tag, or joint, that they will be linked at (I.E. "tag_torso").
  void LinkModel(t3DModel *pModel, t3DModel *pLink, const char * strTagName);

  // This takes a string of an animation and sets the torso animation accordingly
  void SetTorsoAnimation(const char * strAnimation);

  // This takes a string of an animation and sets the legs animation accordingly
  void SetLegsAnimation(const char * strAnimation);

  // This renders the character to the screen
  void DrawModel();

  // j.c. Update model: TODO separate per-player data from shared model data
  void Update();

  // This frees the character's data
  void DestroyModel(t3DModel *pModel);

  // This returns a pointer to a .md3 model in the character (kLower, kUpper, kHead, kWeapon)
  t3DModel *GetModel(int whichPart);

private:
  // This loads the models textures with a given path
  bool LoadModelTextures(t3DModel *pModel, const std::string& strPath, resource_manager& rm);

  // This loads the animation config file (.cfg) for the character
  bool LoadAnimations(const std::string& strConfigFile);

  // This updates the models current frame of animation, and calls SetCurrentTime()
  void UpdateModel(t3DModel *pModel);

  // This sets the lastTime, t, and the currentFrame of the models animation when needed
  void SetCurrentTime(t3DModel *pModel);

  // This recursively draws the character models, starting with the lower.md3 model
  void DrawLink(t3DModel *pModel);

  // This a md3 model to the screen (not the whole character)
  void RenderModel(t3DModel *pModel);

  // Member Variables

  // This stores the texture array for each of the textures assigned to this model
  //unsigned int /*UINT*/ m_Textures[MAX_TEXTURES];	

  // This stores a list of all the names of the textures that have been loaded.  
  // This was created so that we could check to see if a texture that is assigned
  // to a mesh has already been loaded.  If so, then we don't need to load it again
  // and we can assign the textureID to the same textureID as the first loaded texture.
  // You could get rid of this variable by doing something tricky in the texture loading
  // function, but I didn't want to make it too confusing to load the textures.
  std::vector<std::string> strTextures;

  // These are are models for the character's head and upper and lower body parts
  t3DModel m_Head;
  t3DModel m_Upper;
  t3DModel m_Lower;

  // This store the players weapon model (optional load)
  t3DModel m_Weapon;
};

// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
// The Quake3 .Md3 file format is owned by ID Software.  This tutorial is being used 
// as a teaching tool to help understand model loading and animation.  This should
// not be sold or used under any way for commercial use with out written consent
// from ID Software.
//
// Quake, Quake2 and Quake3 are trademarks of ID Software.
// Lara Croft is a trademark of Eidos and should not be used for any commercial gain.
// All trademarks used are properties of their respective owners. 
//
//

