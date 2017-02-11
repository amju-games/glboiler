// -----------------------------------------------------------------------------
// glboiler - Jason Colman 2016-2017 - OpenGL experiments
// -----------------------------------------------------------------------------

// Modified from www.gametutorials.com, original author Ben Humphrey, digiben@gametutorials.com

#include <fstream>
#include <iostream>
#include <cmath>

#ifdef WIN32
// TODO TEMP HACK - timeGetTime
#include <Windows.h>
#endif

#include "gl_includes.h"
#include "log.h"
#include "md3.h"
#include "string_utils.h"

//#define MD3_DEBUG

static bool IsInString(std::string strString, std::string strSubString)
{
  // Make sure both of these strings are valid, return false if any are empty
  if (strString.length() <= 0 || strSubString.length() <= 0) return false;

  // grab the starting index where the sub string is in the original string
  unsigned int index = strString.find(strSubString);

  // Make sure the index returned was valid
  if (index < strString.length())
    return true;

  // The sub string does not exist in strString.
  return false;
}

CModelMD3::CModelMD3()
{
  memset(&m_Head, 0, sizeof(t3DModel));
  memset(&m_Upper, 0, sizeof(t3DModel));
  memset(&m_Lower, 0, sizeof(t3DModel));
  memset(&m_Weapon, 0, sizeof(t3DModel));
}

CModelMD3::~CModelMD3()
{
  DestroyModel(&m_Head);
  DestroyModel(&m_Upper);
  DestroyModel(&m_Lower);
  DestroyModel(&m_Weapon);
}

void CModelMD3::DestroyModel(t3DModel *pModel)
{
  // Go through all the objects in the model
  for (int i = 0; i < pModel->numOfObjects; i++)
  {
    // Free the faces, normals, vertices, and texture coordinates.
    if (pModel->pObject[i].pFaces)		delete[] pModel->pObject[i].pFaces;
    if (pModel->pObject[i].pNormals)		delete[] pModel->pObject[i].pNormals;
    if (pModel->pObject[i].pVerts)		delete[] pModel->pObject[i].pVerts;
    if (pModel->pObject[i].pTexVerts)	delete[] pModel->pObject[i].pTexVerts;
  }

  // Free the tags associated with this model
  if (pModel->pTags)		delete[] pModel->pTags;

  // Free the links associated with this model (We use free because we used malloc())
  if (pModel->pLinks)		free(pModel->pLinks);
}

t3DModel *CModelMD3::GetModel(int whichPart)
{
  // Return the legs model if desired
  if (whichPart == kLower)
    return &m_Lower;

  // Return the torso model if desired
  if (whichPart == kUpper)
    return &m_Upper;

  // Return the head model if desired
  if (whichPart == kHead)
    return &m_Head;

  // Return the weapon model
  return &m_Weapon;
}

bool CModelMD3::LoadModel(const std::string& strPath, resource_manager& rm) ////, const std::string& strModel)
{
  CLoadMD3 loadMd3;				// This object allows us to load each .md3 and .skin file

  // More standard naming convention
  std::string strLowerModel = strPath + "lower.md3";
  std::string strUpperModel = strPath + "upper.md3";
  std::string strHeadModel = strPath + "head.md3";
  std::string strLowerSkin = strPath + "lower_default.skin";
  std::string strUpperSkin = strPath + "upper_default.skin";
  std::string strHeadSkin = strPath + "head_default.skin";

#ifdef MD3_DEBUG
  log(msg() << "Loading head...");
#endif

  // Load the head mesh (*_head.md3) and make sure it loaded properly
  if (!loadMd3.ImportMD3(&m_Head, strHeadModel))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the HEAD model!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading upper...");
#endif

  // Load the upper mesh (*_head.md3) and make sure it loaded properly
  if (!loadMd3.ImportMD3(&m_Upper, strUpperModel))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the UPPER model!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading lower...");
#endif

  // Load the lower mesh (*_lower.md3) and make sure it loaded properly
  if (!loadMd3.ImportMD3(&m_Lower, strLowerModel))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the LOWER model!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading lower skin...");
#endif

  // Load the lower skin (*_upper.skin) and make sure it loaded properly
  if (!loadMd3.LoadSkin(&m_Lower, strLowerSkin))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the LOWER skin!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading upper skin...");
#endif

  // Load the upper skin (*_upper.skin) and make sure it loaded properly
  if (!loadMd3.LoadSkin(&m_Upper, strUpperSkin))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the UPPER skin!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading head skin...");
#endif

  // Load the head skin (*_head.skin) and make sure it loaded properly
  if (!loadMd3.LoadSkin(&m_Head, strHeadSkin))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the HEAD skin!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading lower textures...");
#endif

  // Load the lower, upper and head textures.  
  if (!LoadModelTextures(&m_Lower, strPath, rm))
  {
    std::cout << "Failed to load LOWER textures.\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading upper textures...");
#endif

  if (!LoadModelTextures(&m_Upper, strPath, rm))
  {
    std::cout << "Failed to load UPPER textures.\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading head textures...");
#endif

  if (!LoadModelTextures(&m_Head, strPath, rm))
  {
    std::cout << "Failed to load HEAD textures.\n";
    return false;
  }

  // Add the path and file name prefix to the animation.cfg file
  /* OLD  from Lara example
      std::string strConfigFile = strPath + strModel + "_animation.cfg";
      */

  // More conventional
  std::string strConfigFile = strPath + "animation.cfg";

#ifdef MD3_DEBUG
  log(msg() << "Loading animations...");
#endif

  // Load the animation config file (*_animation.config) and make sure it loaded properly
  if (!LoadAnimations(strConfigFile))
  {
    // Display an error message telling us the file could not be found
    std::cout << "Unable to load the Animation Config File!\n";
    return false;
  }

#ifdef MD3_DEBUG
  log(msg() << "Loading link...");
#endif

  // Link the lower body to the upper body when the tag "tag_torso" is found in our tag array
  LinkModel(&m_Lower, &m_Upper, "tag_torso");

#ifdef MD3_DEBUG
  log(msg() << "Loading link...");
#endif

  // Link the upper body to the head when the tag "tag_head" is found in our tag array
  LinkModel(&m_Upper, &m_Head, "tag_head");

  // The character was loaded correctly so return true
  return true;
}

bool CModelMD3::LoadWeapon(const std::string& strPath, const std::string& strModel, resource_manager& rm)
{
  CLoadMD3 loadMd3;					// This object allows us to load the.md3 and .shader file

  std::string strWeaponModel = strPath + strModel + ".md3";

  // Load the weapon mesh (*.md3) and make sure it loaded properly
  if (!loadMd3.ImportMD3(&m_Weapon, strWeaponModel))
  {
    std::cout << "Unable to load the WEAPON model!\n";
    return false;
  }

  // Add the path, file name and .shader extension together to get the file name and path
  std::string strWeaponShader = strPath + strModel + ".shader";

  // Load our textures associated with the gun from the weapon shader file
  if (!loadMd3.LoadShader(&m_Weapon, strWeaponShader))
  {
    // Display the error message that we couldn't find the shader file and return false
    std::cout << "Unable to load the SHADER file!\n";
    return false;
  }

  // We should have the textures needed for each weapon part loaded from the weapon's
  // shader, so let's load them in the given path.
  LoadModelTextures(&m_Weapon, strPath, rm);

  // Link the weapon to the model's hand that has the weapon tag
  LinkModel(&m_Upper, &m_Weapon, "tag_weapon");

  // The weapon loaded okay, so let's return true to reflect this
  return true;
}

static gl_texture* CreateTexture(const std::string& file, resource_manager& rm)
{
  std::string f = trim(file);
  std::shared_ptr<gl_texture> tex = rm.get_texture(f);
  return tex.get();
}

bool CModelMD3::LoadModelTextures(t3DModel *pModel, const std::string& strPath, resource_manager& rm)
{
  // Go through all the materials that are assigned to this model
  for (int i = 0; i < pModel->numOfMaterials; i++)
  {
    // Check to see if there is a file name to load in this material
    if (strlen(pModel->pMaterials[i].strFile) > 0)
    {
      // Add the file name and path together so we can load the texture
      //sprintf(strFullPath, "%s", pModel->pMaterials[i].strFile);
      std::string strFullPath = strPath + pModel->pMaterials[i].strFile;

      gl_texture* pTex = CreateTexture(strFullPath, rm);
      if (!pTex)
      {
        std::cout << "Md3: CreateTexture Failed to load texture " << strFullPath << "\n";
        return false;
      }

      // Set the texture ID for this material by getting the current loaded texture count
      pModel->pMaterials[i].textureId = pTex; //strTextures.size();

      // Now we increase the loaded texture count by adding the texture name to our
      // list of texture names.  Remember, this is used so we can check if a texture
      // is already loaded before we load 2 of the same textures.  Make sure you
      // understand what an STL vector list is.  We have a tutorial on it if you don't.
      strTextures.push_back(pModel->pMaterials[i].strFile);
    }
  }
  return true;
}

bool CModelMD3::LoadAnimations(const std::string& strConfigFile)
{
  // This function is given a path and name to an animation config file to load.
  // The implementation of this function is arbitrary, so if you have a better way
  // to parse the animation file, that is just as good.  Whatever works.
  // Basically, what is happening here, is that we are grabbing an animation line:
  //
  // "0	31	0	25		// BOTH_DEATH1"
  //
  // Then parsing it's values.  The first number is the starting frame, the next
  // is the frame count for that animation (endFrame would equal startFrame + frameCount),
  // the next is the looping frames (ignored), and finally the frames per second that
  // the animation should run at.  The end of this line is the name of the animation.
  // Once we get that data, we store the information in our tAnimationInfo object, then
  // after we finish parsing the file, the animations are assigned to each model.  
  // Remember, that only the torso and the legs objects have animation.  It is important
  // to note also that the animation prefixed with BOTH_* are assigned to both the legs
  // and the torso animation list, hence the name "BOTH" :)

  // Create an animation object for every valid animation in the Quake3 Character
  tAnimationInfo animations[MAX_ANIMATIONS];

  text_file f; ///File f(false); // no version info
  bool b = f.open_for_reading(strConfigFile);

  // Here we make sure that the file was found and could be opened
  if (!b)
  {
    // Return an unsuccessful retrieval
    return false;
  }

  std::string strWord;				// This stores the current word we are reading in
  std::string strLine;				// This stores the current line we read in
  int currentAnim = 0;				// This stores the current animation count
  int torsoOffset = 0;				// The offset between the first torso and leg animation

  // Here we go through every word in the file until a numeric number if found.
  // This is how we know that we are on the animation lines, and past header info.
  // This of course isn't the most solid way, but it works fine.  It wouldn't hurt
  // to put in some more checks to make sure no numbers are in the header info.

  while (f.read_string(&strLine)) //Token(&strWord))  //( fin >> strWord)
  {
    strings strs = split(strLine, '\t');
#ifdef MD3_DEBUG
    std::cout << "Got this line: '" << strLine << "' num splits: " << strs.size() << "\n";
#endif

    // If the first character of the word is NOT a number, we haven't hit an animation line
    if (!isdigit(strLine[0]))
    {
#ifdef MD3_DEBUG
      std::cout << "(ignoring this line: " << strLine.c_str() << ")\n";
#endif
      continue;
    }

    // If we get here, we must be on an animation line, so let's parse the data.
    // We should already have the starting frame stored in strWord, so let's extract it.

    // Get the number stored in the strWord string and create some variables for the rest
    int startFrame = to_int(strs[0]); //atoi(strWord.c_str());
    int numOfFrames = to_int(strs[1]);
    int loopingFrames = to_int(strs[2]);
    int framesPerSecond = to_int(strs[3]);

    // Initialize the current animation structure with the data just read in
    animations[currentAnim].startFrame = startFrame;
    animations[currentAnim].endFrame = startFrame + numOfFrames;
    animations[currentAnim].loopingFrames = loopingFrames;
    animations[currentAnim].framesPerSecond = framesPerSecond;

    // Read past the "//" and read in the animation name (I.E. "BOTH_DEATH1").
    // This might not be how every config file is set up, so make sure.
    std::string name = strs[strs.size() - 1];
    name = replace(name, "\t", "");
    name = replace(name, "//", "");
    name = trim(name);

#ifdef MD3_DEBUG
    std::cout 
      << "Start frame: " << startFrame 
      << "\tNum of frames: " << numOfFrames 
      << "\tLooping: " << loopingFrames 
      << "\tFPS: " << framesPerSecond 
      << "\tName: '" << name << "'\n";
#endif

    // Copy the name of the animation to our animation structure
    strcpy_s(animations[currentAnim].strName, name.c_str());

    // If the animation is for both the legs and the torso, add it to their animation list
    if (IsInString(name, "BOTH"))
    {
      // Add the animation to each of the upper and lower mesh lists
      m_Upper.pAnimations.push_back(animations[currentAnim]);
      m_Lower.pAnimations.push_back(animations[currentAnim]);
    }
    // If the animation is for the torso, add it to the torso's list
    else if (IsInString(name, "TORSO"))
    {
      m_Upper.pAnimations.push_back(animations[currentAnim]);
    }
    // If the animation is for the legs, add it to the legs's list
    else if (IsInString(name, "LEGS"))
    {
      // Because I found that some config files have the starting frame for the
      // torso and the legs a different number, we need to account for this by finding
      // the starting frame of the first legs animation, then subtracting the starting
      // frame of the first torso animation from it.  For some reason, some exporters
      // might keep counting up, instead of going back down to the next frame after the
      // end frame of the BOTH_DEAD3 anim.  This will make your program crash if so.

      // If the torso offset hasn't been set, set it
      if (!torsoOffset)
        torsoOffset = animations[LEGS_WALKCR].startFrame - animations[TORSO_GESTURE].startFrame;

      // Minus the offset from the legs animation start and end frame.
      animations[currentAnim].startFrame -= torsoOffset;
      animations[currentAnim].endFrame -= torsoOffset;

      // Add the animation to the list of leg animations
      m_Lower.pAnimations.push_back(animations[currentAnim]);
    }

    // Increase the current animation count
    currentAnim++;
  }

  // Store the number if animations for each list by the STL vector size() function
  m_Lower.numOfAnimations = m_Lower.pAnimations.size();
  m_Upper.numOfAnimations = m_Upper.pAnimations.size();
  m_Head.numOfAnimations = m_Head.pAnimations.size();
  m_Weapon.numOfAnimations = m_Head.pAnimations.size();

  // Return a success
  return true;
}

void  CModelMD3::LinkModel(t3DModel *pModel, t3DModel *pLink, const char * strTagName)
{
  // Make sure we have a valid model, link and tag name, otherwise quit this function
  if (!pModel || !pLink || !strTagName) return;

  // Go through all of our tags and find which tag contains the strTagName, then link'em
  for (int i = 0; i < pModel->numOfTags; i++)
  {
    // If this current tag index has the tag name we are looking for
    if (!strcmp(pModel->pTags[i].strName, strTagName))
    {
      // Link the model's link index to the link (or model/mesh) and return
      pModel->pLinks[i] = pLink;
      return;
    }
  }
}

void CModelMD3::UpdateModel(t3DModel *pModel)
{
  // Initialize a start and end frame, for models with no animation
  int startFrame = 0;
  int endFrame = 1;

  // This function is used to keep track of the current and next frames of animation
  // for each model, depending on the current animation.  Some models down have animations,
  // so there won't be any change.

  // Here we grab the current animation that we are on from our model's animation list
  tAnimationInfo *pAnim = &(pModel->pAnimations[pModel->currentAnim]);

  // If there is any animations for this model
  if (pModel->numOfAnimations)
  {
    // Set the starting and end frame from for the current animation
    startFrame = pAnim->startFrame;
    endFrame = pAnim->endFrame;
  }

  // This gives us the next frame we are going to.  We mod the current frame plus
  // 1 by the current animations end frame to make sure the next frame is valid.
  pModel->nextFrame = (pModel->currentFrame + 1) % endFrame;

  // If the next frame is zero, that means that we need to start the animation over.
  // To do this, we set nextFrame to the starting frame of this animation.
  if (pModel->nextFrame == 0)
    pModel->nextFrame = startFrame;

  // Next, we want to get the current time that we are interpolating by.  Remember,
  // if t = 0 then we are at the beginning of the animation, where if t = 1 we are at the end.
  // Anything from 0 to 1 can be thought of as a percentage from 0 to 100 percent complete.
  SetCurrentTime(pModel);
}

void CModelMD3::Update()
{
  // Update the leg and torso animations
  // TODO Break up shared and per-player data
  UpdateModel(&m_Lower);
  UpdateModel(&m_Upper);
}

void CModelMD3::DrawModel()
{
  // Rotate the model to compensate for the z up orientation that the model was saved

  // NB this is only OK for the gl_1_1 renderer! - j.c.
  // Better to not do this, for consistency with gl 2+ 
  ////    glRotatef(-90, 1, 0, 0);

  // Draw the first link, which is the lower body.  This will then recursively go
  // through the models attached to this model and drawn them.
  DrawLink(&m_Lower);
}

void CModelMD3::DrawLink(t3DModel *pModel)
{
  // Draw the current model passed in (Initially the legs)
  RenderModel(pModel);

  // Though the changes to this function from the previous tutorial aren't huge, they
  // are pretty powerful.  Since animation is in effect, we need to create a rotational
  // matrix for each key frame, at each joint, to be applied to the child nodes of that 
  // object.  We can also slip in the interpolated translation into that same matrix.
  // The big thing in this function is interpolating between the 2 rotations.  The process
  // involves creating 2 quaternions from the current and next key frame, then using
  // slerp (spherical linear interpolation) to find the interpolated quaternion, then
  // converting that quaternion to a 4x4 matrix, adding the interpolated translation
  // to that matrix, then finally applying it to the current model view matrix in OpenGL.
  // This will then effect the next objects that are somehow explicitly or inexplicitly
  // connected and drawn from that joint.

  // Create some local variables to store all this crazy interpolation data
  quat qQuat, qNextQuat, qInterpolatedQuat;
  float *pMatrix, *pNextMatrix;
  float finalMatrix[16] = { 0 };

  // Now we need to go through all of this models tags and draw them.
  for (int i = 0; i < pModel->numOfTags; i++)
  {
    // Get the current link from the models array of links (Pointers to models)
    t3DModel *pLink = pModel->pLinks[i];

    // If this link has a valid address, let's draw it!
    if (pLink)
    {
      // To find the current translation position for this frame of animation, we times
      // the currentFrame by the number of tags, then add i.  This is similar to how
      // the vertex key frames are interpolated.
      vec3 vPosition = pModel->pTags[pModel->currentFrame * pModel->numOfTags + i].vPosition;

      // Grab the next key frame translation position
      vec3 vNextPosition = pModel->pTags[pModel->nextFrame * pModel->numOfTags + i].vPosition;

      // By using the equation: p(t) = p0 + t(p1 - p0), with a time t,
      // we create a new translation position that is closer to the next key frame.
      vPosition.x = vPosition.x + pModel->t * (vNextPosition.x - vPosition.x),
        vPosition.y = vPosition.y + pModel->t * (vNextPosition.y - vPosition.y),
        vPosition.z = vPosition.z + pModel->t * (vNextPosition.z - vPosition.z);

      // Now comes the more complex interpolation.  Just like the translation, we
      // want to store the current and next key frame rotation matrix, then interpolate
      // between the 2.

      // Get a pointer to the start of the 3x3 rotation matrix for the current frame
      pMatrix = &pModel->pTags[pModel->currentFrame * pModel->numOfTags + i].rotation[0][0];

      // Get a pointer to the start of the 3x3 rotation matrix for the next frame
      pNextMatrix = &pModel->pTags[pModel->nextFrame * pModel->numOfTags + i].rotation[0][0];

      // Now that we have 2 1D arrays that store the matrices, let's interpolate them

      // Convert the current and next key frame 3x3 matrix into a quaternion
      qQuat.CreateFromMatrix(pMatrix, 3);
      qNextQuat.CreateFromMatrix(pNextMatrix, 3);

      // Using spherical linear interpolation, we find the interpolated quaternion
      qInterpolatedQuat = qQuat.Slerp(qQuat, qNextQuat, pModel->t);

      // Here we convert the interpolated quaternion into a 4x4 matrix
      qInterpolatedQuat.CreateMatrix(finalMatrix);

      // To cut out the need for 2 matrix calls, we can just slip the translation
      // into the same matrix that holds the rotation.  That is what index 12-14 holds.
      finalMatrix[12] = vPosition.x;
      finalMatrix[13] = vPosition.y;
      finalMatrix[14] = vPosition.z;

      glPushMatrix();
      glMultMatrixf(finalMatrix);

      // Recursively draw the next model that is linked to the current one.
      // This could either be a body part or a gun that is attached to
      // the hand of the upper body model.
      DrawLink(pLink);

      glPopMatrix();
    }
  }

}

void CModelMD3::SetCurrentTime(t3DModel *pModel)
{
  float elapsedTime = 0.0f;

  // This function is very similar to finding the frames per second.
  // Instead of checking when we reach a second, we check if we reach
  // 1 second / our animation speed. (1000 ms / animationSpeed).
  // That's how we know when we need to switch to the next key frame.
  // In the process, we get the t value for how far we are at to going to the
  // next animation key frame.  We use time to do the interpolation, that way
  // it runs the same speed on any persons computer, regardless of their specs.
  // It might look choppier on a junky computer, but the key frames still be
  // changing the same time as the other persons, it will just be not as smooth
  // of a transition between each frame.  The more frames per second we get, the
  // smoother the animation will be.  Since we are working with multiple models 
  // we don't want to create static variables, so the t and elapsedTime data are 
  // stored in the model's structure.

  // Return if there is no animations in this model
  if (!pModel->pAnimations.size())
  {
    return;
  }

  // Get the current time in milliseconds
#ifdef WIN32
  float time = timeGetTime(); // TODO TEMP TEST - Windows only
#endif

#ifdef MACOSX
  float time = 1.f;
#endif
  // TODO Sort this out. 

  // Find the time that has elapsed since the last time that was stored
  elapsedTime = time - pModel->lastTime;

  // Store the animation speed for this animation in a local variable
  int animationSpeed = pModel->pAnimations[pModel->currentAnim].framesPerSecond;

  // To find the current t we divide the elapsed time by the ratio of:
  //
  // (1_second / the_animation_frames_per_second)
  //
  // Since we are dealing with milliseconds, we need to use 1000
  // milliseconds instead of 1 because we are using GetTickCount(), which is in 
  // milliseconds. 1 second == 1000 milliseconds.  The t value is a value between 
  // 0 to 1.  It is used to tell us how far we are from the current key frame to 
  // the next key frame.
  float t = elapsedTime / (1000.0f / animationSpeed);

  // If our elapsed time goes over the desired time segment, start over and go 
  // to the next key frame.
  if (elapsedTime >= (1000.0f / animationSpeed))
  {
    // Set our current frame to the next key frame (which could be the start of the anim)
    pModel->currentFrame = pModel->nextFrame;

    // Set our last time for the model to the current time
    pModel->lastTime = time;
  }

  // Set the t for the model to be used in interpolation
  pModel->t = t;
}

void CModelMD3::RenderModel(t3DModel *pModel)
{
  // Make sure we have valid objects just in case. (size() is in the STL vector class)
  if (pModel->pObject.size() <= 0)
  {
    log(msg() << "Invalid md3 object!");
    return;
  }

  // Go through all of the objects stored in this model
  for (int i = 0; i < pModel->numOfObjects; i++)
  {
    // Get the current object that we are displaying
    t3DObject *pObject = &pModel->pObject[i];

    // Now that we have animation for our model, we need to interpolate between
    // the vertex key frames.  The .md3 file format stores all of the vertex 
    // key frames in a 1D array.  This means that in order to go to the next key frame,
    // we need to follow this equation:  currentFrame * numberOfVertices
    // That will give us the index of the beginning of that key frame.  We just
    // add that index to the initial face index, when indexing into the vertex array.

    // Find the current starting index for the current key frame we are on
    int currentIndex = pModel->currentFrame * pObject->numOfVerts;

    // Since we are interpolating, we also need the index for the next key frame
    int nextIndex = pModel->nextFrame * pObject->numOfVerts;

    // If the object has a texture assigned to it, let's bind it to the model.
    // This isn't really necessary since all models have textures, but I left this
    // in here to keep to the same standard as the rest of the model loaders.
    if (pObject->bHasTexture)
    {
      // Turn on texture mapping
      //glEnable(GL_TEXTURE_2D);
      //AmjuGL::Enable(AmjuGL::AMJU_TEXTURE_2D);

      // Grab the texture index from the materialID index into our material list
      gl_texture* pTex = pModel->pMaterials[pObject->materialID].textureId;
      //TODO TEMP TEST
      pTex->use_on_gl_thread();
      //UseThisTexture(); //Bind();
      // Bind the texture index that we got from the material textureID
      //glBindTexture(GL_TEXTURE_2D, m_Textures[textureID]);
    }
    else
    {
      // Turn off texture mapping
      //glDisable(GL_TEXTURE_2D);
      //AmjuGL::Disable(AmjuGL::AMJU_TEXTURE_2D);
    }

    //      log(msg() << "Drawing " << pObject->numOfFaces << " faces");

    // Start drawing our model triangles
    glBegin(GL_TRIANGLES);

    // Go through all of the faces (polygons) of the object and draw them
    for (int j = 0; j < pObject->numOfFaces; j++)
    {
      // Go through each vertex of the triangle and draw it.
      for (int whichVertex = 0; whichVertex < 3; whichVertex++)
      {
        // Get the index for the current point in the face list
        int index = pObject->pFaces[j].vertIndex[whichVertex];

        // Make sure there is texture coordinates for this (%99.9 likelyhood)
        if (pObject->pTexVerts)
        {
          // Assign the texture coordinate to this vertex
          glTexCoord2f(pObject->pTexVerts[index].x,
            pObject->pTexVerts[index].y);
        }

        // Like in the MD2 Animation tutorial, we use linear interpolation
        // between the current and next point to find the point in between,
        // depending on the model's "t" (0.0 to 1.0).

        // Store the current and next frame's vertex by adding the current
        // and next index to the initial index given from the face data.
        vec3 vPoint1 = pObject->pVerts[currentIndex + index];
        vec3 vPoint2 = pObject->pVerts[nextIndex + index];

        vec3 normal1 = pObject->pNormals[currentIndex + index];
        vec3 normal2 = pObject->pNormals[nextIndex + index];
        vec3 norm = normal1 + (normal2 - normal1) * pModel->t;
        glNormal3f(norm.x, norm.y, norm.z);

        // By using the equation: p(t) = p0 + t(p1 - p0), with a time t,
        // we create a new vertex that is closer to the next key frame.
        glVertex3f(vPoint1.x + pModel->t * (vPoint2.x - vPoint1.x),
          vPoint1.y + pModel->t * (vPoint2.y - vPoint1.y),
          vPoint1.z + pModel->t * (vPoint2.z - vPoint1.z));
      }
    }

    // Stop drawing polygons
    glEnd();
  }
}

void CModelMD3::SetTorsoAnimation(const char *  strAnimation)
{
  // Go through all of the animations in this model
  for (int i = 0; i < m_Upper.numOfAnimations; i++)
  {
    // If the animation name passed in is the same as the current animation's name
    if (!strcmp(m_Upper.pAnimations[i].strName, strAnimation))
    {
      // Set the legs animation to the current animation we just found and return
      m_Upper.currentAnim = i;
      m_Upper.currentFrame = m_Upper.pAnimations[m_Upper.currentAnim].startFrame;
      return;
    }
  }
}

void CModelMD3::SetLegsAnimation(const char *  strAnimation)
{
  // Go through all of the animations in this model
  for (int i = 0; i < m_Lower.numOfAnimations; i++)
  {
    // If the animation name passed in is the same as the current animation's name
    if (!strcmp(m_Lower.pAnimations[i].strName, strAnimation))
    {
      // Set the legs animation to the current animation we just found and return
      m_Lower.currentAnim = i;
      m_Lower.currentFrame = m_Lower.pAnimations[m_Lower.currentAnim].startFrame;

      return;
    }
  }
  std::cout << "** FAILED TO FIND LEGS ANIM " << strAnimation << "\n";
}

CLoadMD3::CLoadMD3()
{
  // Here we initialize our structures to 0
  memset(&m_Header, 0, sizeof(tMd3Header));

  // Set the pointers to null
  m_pSkins = NULL;
  m_pTexCoords = NULL;
  m_pTriangles = NULL;
  m_pBones = NULL;

  m_bytesRead = 0;
}

bool CLoadMD3::ImportMD3(t3DModel *pModel, const std::string& strFileName)
{
#ifdef MD3_DEBUG
  std::cout << "LOADING MODEL: " << strFileName << "\n";
#endif

  // Open the MD3 file in binary
  std::string filepluspath = "";
  filepluspath += strFileName;
  m_pFile = new binary_file; // no version info
  bool b = m_pFile->open_for_reading(filepluspath);
  m_bytesRead = 0;

  // Make sure we have a valid file pointer (we found the file)
  if (!b)
  {
    // Display an error message and don't load anything if no file was found
    return false;
  }
#ifdef MD3_DEBUG
  std::cout << "Opened " << strFileName << " ok.\n";
#endif
  // Read the header data and store it in our m_Header member variable
  m_bytesRead += m_pFile->read_binary(sizeof(tMd3Header), (unsigned char *)&m_Header);
  // Get the 4 character ID
  char *ID = m_Header.fileID;

  // The ID MUST equal "IDP3" and the version MUST be 15, or else it isn't a valid
  // .MD3 file.  This is just the numbers ID Software chose.

  // Make sure the ID == IDP3 and the version is this crazy number '15' or else it's a bad egg
  if ((ID[0] != 'I' || ID[1] != 'D' || ID[2] != 'P' || ID[3] != '3') || m_Header.version != 15)
  {
    // Display an error message for bad file format, then stop loading
    std::cout << "Invalid file format (Version not 15): " << strFileName << "\n";
    std::cout << "ID found: " << m_Header.version << "\n";
    return false;
  }

  // Read in the model and animation data
  ReadMD3Data(pModel);

  // Clean up after everything
  CleanUp();

  return true;
}

void CLoadMD3::ReadMD3Data(t3DModel *pModel)
{
  int i = 0;

  // Here we allocate memory for the bone information and read the bones in.
  m_pBones = new tMd3Bone[m_Header.numFrames];
  m_bytesRead += m_pFile->read_binary(sizeof(tMd3Bone) * m_Header.numFrames, (unsigned char *)m_pBones);
#ifdef MD3_DEBUG
  std::cout << "Read bone info, discarding for now.\n";
#endif


  // Since we don't care about the bone positions, we just free it immediately.
  // It might be cool to display them so you could get a visual of them with the model.

  // Free the unused bones
  delete[] m_pBones;

  // Next, after the bones are read in, we need to read in the tags.  Below we allocate
  // memory for the tags and then read them in.  For every frame of animation there is
  // an array of tags.
  pModel->pTags = new tMd3Tag[m_Header.numFrames * m_Header.numTags];

  m_bytesRead += m_pFile->read_binary(sizeof(tMd3Tag) * m_Header.numFrames * m_Header.numTags,
    (unsigned char *)pModel->pTags);

  // Assign the number of tags to our model
  pModel->numOfTags = m_Header.numTags;

  // Now we want to initialize our links.  Links are not read in from the .MD3 file, so
  // we need to create them all ourselves.  We use a double array so that we can have an
  // array of pointers.  We don't want to store any information, just pointers to t3DModels.
  pModel->pLinks = (t3DModel **)malloc(sizeof(t3DModel) * m_Header.numTags);

  // Initilialize our link pointers to NULL
  for (i = 0; i < m_Header.numTags; i++)
    pModel->pLinks[i] = NULL;

  // Get the current offset into the file
  unsigned int meshOffset = m_bytesRead;

  // Create a local meshHeader that stores the info about the mesh
  tMd3MeshInfo meshHeader;

  // Go through all of the sub-objects in this mesh
  for (i = 0; i < m_Header.numMeshes; i++)
  {
#ifdef MD3_DEBUG
    std::cout << "Loading sub-object " << i << " of " << m_Header.numMeshes << "...\n";
#endif

    // Seek to the start of this mesh and read in it's header
    m_pFile->seek(meshOffset);

    m_pFile->read_binary(sizeof(tMd3MeshInfo), (unsigned char *)&meshHeader);

    // Here we allocate all of our memory from the header's information
    m_pSkins = new tMd3Skin[meshHeader.numSkins];
    m_pTexCoords = new tMd3TexCoord[meshHeader.numVertices];
    m_pTriangles = new tMd3Face[meshHeader.numTriangles];
    m_pVertices = new tMd3Triangle[meshHeader.numVertices * meshHeader.numMeshFrames];

    // Read in the skin information
    m_pFile->read_binary(sizeof(tMd3Skin) * meshHeader.numSkins, (unsigned char *)m_pSkins);

    // Seek to the start of the triangle/face data, then read it in
    m_pFile->seek(meshOffset + meshHeader.triStart);

    m_pFile->read_binary(sizeof(tMd3Face) * meshHeader.numTriangles, (unsigned char *)m_pTriangles);

    // Seek to the start of the UV coordinate data, then read it in
    m_pFile->seek(meshOffset + meshHeader.uvStart);

    m_pFile->read_binary(sizeof(tMd3TexCoord) * meshHeader.numVertices, (unsigned char *)m_pTexCoords);

    // Seek to the start of the vertex/face index information, then read it in.
    m_pFile->seek(meshOffset + meshHeader.vertexStart);

    m_pFile->read_binary(sizeof(tMd3Triangle) * meshHeader.numMeshFrames *
      meshHeader.numVertices, (unsigned char *)m_pVertices);

    // Now that we have the data loaded into the Quake3 structures, let's convert them to
    // our data types like t3DModel and t3DObject.  That way the rest of our model loading
    // code will be mostly the same as the other model loading tutorials.
    ConvertDataStructures(pModel, meshHeader);

    // Free all the memory for this mesh since we just converted it to our structures
    delete[] m_pSkins;
    delete[] m_pTexCoords;
    delete[] m_pTriangles;
    delete[] m_pVertices;

    // Increase the offset into the file
    meshOffset += meshHeader.meshSize;
  }
}

void CLoadMD3::ConvertDataStructures(t3DModel *pModel, tMd3MeshInfo meshHeader)
{
  int i = 0;

  // Increase the number of objects (sub-objects) in our model since we are loading a new one
  pModel->numOfObjects++;

  // Create a empty object structure to store the object's info before we add it to our list
  t3DObject currentMesh = { 0 };

  // Copy the name of the object to our object structure
  strcpy_s(currentMesh.strName, meshHeader.strName);

  // Assign the vertex, texture coord and face count to our new structure
  currentMesh.numOfVerts = meshHeader.numVertices;
  currentMesh.numTexVertex = meshHeader.numVertices;
  currentMesh.numOfFaces = meshHeader.numTriangles;

  // Allocate memory for the vertices, texture coordinates and face data.
  // Notice that we multiply the number of vertices to be allocated by the
  // number of frames in the mesh.  This is because each frame of animation has a 
  // totally new set of vertices.  This will be used in the next animation tutorial.
  currentMesh.pVerts = new vec3[currentMesh.numOfVerts * meshHeader.numMeshFrames];

  // j.c. 
  currentMesh.pNormals = new vec3[currentMesh.numOfVerts * meshHeader.numMeshFrames];

  currentMesh.pTexVerts = new vec2[currentMesh.numOfVerts];
  currentMesh.pFaces = new tFace[currentMesh.numOfFaces];

  // Go through all of the vertices and assign them over to our structure
  for (i = 0; i < currentMesh.numOfVerts * meshHeader.numMeshFrames; i++)
  {
    // For some reason, the ratio 64 is what we need to divide the vertices by,
    // otherwise the model is gargantuanly huge!  If you use another ratio, it
    // screws up the model's body part position.  I found this out by just
    // testing different numbers, and I came up with 65.  I looked at someone
    // else's code and noticed they had 64, so I changed it to that.  I have never
    // read any documentation on the model format that justifies this number, but
    // I can't get it to work without it.  Who knows....  Maybe it's different for
    // 3D Studio Max files verses other software?  You be the judge.  I just work here.. :)
    currentMesh.pVerts[i].x = m_pVertices[i].vertex[0] / 64.0f;
    currentMesh.pVerts[i].y = m_pVertices[i].vertex[1] / 64.0f;
    currentMesh.pVerts[i].z = m_pVertices[i].vertex[2] / 64.0f;

    currentMesh.pNormals[i] = m_pVertices[i].decodedNormal(); // j.c.
  }

  // Go through all of the uv coords and assign them over to our structure
  for (i = 0; i < currentMesh.numTexVertex; i++)
  {
    // Since I changed the image to bitmaps, we need to negate the V ( or y) value.
    // This is because I believe that TARGA (.tga) files, which were originally used
    // with this model, have the pixels flipped horizontally.  If you use other image
    // files and your texture mapping is crazy looking, try deleting this negative.
    currentMesh.pTexVerts[i].x = m_pTexCoords[i].textureCoord[0];
    currentMesh.pTexVerts[i].y = -m_pTexCoords[i].textureCoord[1];
  }

  // Go through all of the face data and assign it over to OUR structure
  for (i = 0; i < currentMesh.numOfFaces; i++)
  {
    // Assign the vertex indices to our face data
    currentMesh.pFaces[i].vertIndex[0] = m_pTriangles[i].vertexIndices[0];
    currentMesh.pFaces[i].vertIndex[1] = m_pTriangles[i].vertexIndices[1];
    currentMesh.pFaces[i].vertIndex[2] = m_pTriangles[i].vertexIndices[2];

    // Assign the texture coord indices to our face data (same as the vertex indices)
    currentMesh.pFaces[i].coordIndex[0] = m_pTriangles[i].vertexIndices[0];
    currentMesh.pFaces[i].coordIndex[1] = m_pTriangles[i].vertexIndices[1];
    currentMesh.pFaces[i].coordIndex[2] = m_pTriangles[i].vertexIndices[2];
  }

  // Here we add the current object to our list object list
  pModel->pObject.push_back(currentMesh);
}

bool CLoadMD3::LoadSkin(t3DModel *pModel, const std::string& strSkin)
{
  // Make sure valid data was passed in
  if (!pModel) return false;

  // Open the skin file
  text_file f; //File f(false); // no version info
  bool b = f.open_for_reading(strSkin);

  // Make sure the file was opened
  if (!b)
  {
    // Display the error message and return false
    std::cout << "Unable to load skin!\n";
    return false;
  }

  // These 2 variables are for reading in each line from the file, then storing
  // the index of where the bitmap name starts after the last '/' character.
  std::string strLine = "";
  int textureNameStart = 0;

  // Go through every line in the .skin file
  while (f.read_string(&strLine)) //(getline(fin, strLine))
  {
    // Loop through all of our objects to test if their name is in this line
    for (int i = 0; i < pModel->numOfObjects; i++)
    {
      // Check if the name of this object appears in this line from the skin file
      if (IsInString(strLine, pModel->pObject[i].strName))
      {
        // To abstract the texture name, we loop through the string, starting
        // at the end of it until we find a '/' character, then save that index + 1.
        for (int j = strLine.length() - 1; j > 0; j--)
        {
          // If this character is a '/', save the index + 1
          if (strLine[j] == '/')
          {
            // Save the index + 1 (the start of the texture name) and break
            textureNameStart = j + 1;
            break;
          }
        }

        // Create a local material info structure
        tMaterialInfo texture;

        // Copy the name of the file into our texture file name variable.
        strcpy_s(texture.strFile, &strLine[textureNameStart]);
#ifdef MD3_DEBUG
        std::cout << "Reading skin file: " << strSkin << ", found texture: " << texture.strFile << "\n";
#endif

        // The tile or scale for the UV's is 1 to 1 
        texture.uTile = texture.uTile = 1;

        // Store the material ID for this object and set the texture boolean to true
        pModel->pObject[i].materialID = pModel->numOfMaterials;
        pModel->pObject[i].bHasTexture = true;

        // Here we increase the number of materials for the model
        pModel->numOfMaterials++;

        // Add the local material info structure to our model's material list
        pModel->pMaterials.push_back(texture);
      }
    }
  }

  return true;
}

bool CLoadMD3::LoadShader(t3DModel *pModel, const std::string& strShader)
{
  // Make sure valid data was passed in
  if (!pModel) return false;

  // Open the shader file
  text_file f;
  bool b = f.open_for_reading(strShader);

  // Make sure the file was opened
  if (!b)
  {
    // Display the error message and return false
    std::cout << "Unable to load shader!\n";
    return false;
  }

  // These variables are used to read in a line at a time from the file, and also
  // to store the current line being read so that we can use that as an index for the 
  // textures, in relation to the index of the sub-object loaded in from the weapon model.
  std::string strLine;
  int currentIndex = 0;

  // Go through and read in every line of text from the file
  while (f.read_string(&strLine))  //(getline(fin, strLine))
  {
    // Create a local material info structure
    tMaterialInfo texture;

    // Copy the name of the file into our texture file name variable
    strcpy_s(texture.strFile, strLine.c_str());

    // The tile or scale for the UV's is 1 to 1 
    texture.uTile = texture.uTile = 1;

    // Store the material ID for this object and set the texture boolean to true
    pModel->pObject[currentIndex].materialID = pModel->numOfMaterials;
    pModel->pObject[currentIndex].bHasTexture = true;

    // Here we increase the number of materials for the model
    pModel->numOfMaterials++;

    // Add the local material info structure to our model's material list
    pModel->pMaterials.push_back(texture);

    // Here we increase the material index for the next texture (if any)
    currentIndex++;
  }

  return true;
}

void CLoadMD3::CleanUp()
{
}

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

