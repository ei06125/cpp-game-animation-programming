#ifndef _H_CHAPTER12SAMPLE03_
#define _H_CHAPTER12SAMPLE03_

#include "Application.h"
#include "Clip.h"
#include "DebugDraw.h"
#include "Mesh.h"
#include "Pose.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter12Sample03 : public Application {
  protected:
	Texture *mDiffuseTexture;
	Shader *mStaticShader;
	Shader *mSkinnedShader;
	std::vector<Mesh> mMeshes;
	std::vector<mat4> mPosePalette;
	Skeleton mSkeleton;
	Pose mCurrentPose;
	std::vector<Clip> mClips;
	unsigned int mCurrentClip;
	float mPlaybackTime;
	DebugDraw *mBindPoseVisual;
	DebugDraw *mRestPoseVisual;
	DebugDraw *mCurrentPoseVisual;

	int mAdditiveIndex;
	float mAdditiveTime;
	Pose mAddPose;
	Pose mAdditiveBase;

	char **mUIClipNames;
	char **mSkinningNames;
	unsigned int mNumUIClips;
	bool mShowRestPose;
	bool mShowCurrentPose;
	bool mShowBindPose;
	SkinningType mSkinType;

  public:
	void Initialize();
	void Update(float deltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
	void ImGui(nk_context *inContext);
};

#endif
