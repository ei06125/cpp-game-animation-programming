#ifndef _H_CHAPTER15SAMPLE01_
#define _H_CHAPTER15SAMPLE01_

#include "AnimTexture.h"
#include "Application.h"
#include "Clip.h"
#include "Crowd.h"
#include "DebugDraw.h"
#include "Mesh.h"
#include "Pose.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter15Sample01 : public Application {
  protected:
	Texture *mDiffuseTexture;
	Shader *mCrowdShader;
	std::vector<Mesh> mMeshes;
	Skeleton mSkeleton;
	std::vector<Clip> mClips;
	std::vector<AnimTexture> mTextures;
	std::vector<Crowd> mCrowds;

  protected:
	void SetCrowdSize(unsigned int size);

  public:
	void Initialize();
	void Update(float deltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
	void ImGui(nk_context *inContext);
};

#endif
