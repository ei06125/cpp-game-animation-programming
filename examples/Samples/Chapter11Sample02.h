#ifndef _H_CHAPTER11SAMPLE02_
#define _H_CHAPTER11SAMPLE02_

#include "Application.h"
#include "Clip.h"
#include "DebugDraw.h"
#include "Mesh.h"
#include "Pose.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter11Sample02 : public Application {
  protected:
	Texture *mDiffuseTexture;
	Shader *mStaticShader;
	Shader *mSkinnedShader;
	std::vector<Mesh> mMeshes;
	std::vector<mat4> mPosePalette;
	Skeleton mSkeleton;
	Pose mCurrentPose;
	std::vector<FastClip> mClips;
	unsigned int mCurrentClip;
	float mPlaybackTime;
	DebugDraw *mBindPoseVisual;
	DebugDraw *mRestPoseVisual;
	DebugDraw *mCurrentPoseVisual;

	char **mUIClipNames;
	char **mSkinningNames;
	unsigned int mNumUIClips;
	bool mShowRestPose;
	bool mShowCurrentPose;
	bool mShowBindPose;
	bool mShowMeshes;
	SkinningType mSkinType;

  public:
	void Initialize();
	void Update(float deltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
	void ImGui(nk_context *inContext);
};

#endif
