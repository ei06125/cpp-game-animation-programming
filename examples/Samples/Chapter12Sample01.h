#ifndef _H_CHAPTER12SAMPLE01_
#define _H_CHAPTER12SAMPLE01_

#include "Application.h"
#include "Blending.h"
#include "Clip.h"
#include "DebugDraw.h"
#include "Mesh.h"
#include "Pose.h"
#include "SamplePoseInstance.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter12Sample01 : public Application {
  protected:
	Texture *mDiffuseTexture;
	Shader *mStaticShader;
	Shader *mSkinnedShader;
	std::vector<Mesh> mMeshes;
	std::vector<mat4> mPosePalette;
	Skeleton mSkeleton;
	std::vector<Clip> mClips;

	DebugDraw *mBindPoseVisual;
	DebugDraw *mRestPoseVisual;
	DebugDraw *mCurrentPoseVisual;

	SamplePoseInstance mAniamtionA;
	SamplePoseInstance mAniamtionB;
	float mBlendFactor;
	unsigned int mBlendRoot;
	Pose mBlendedPose;

	char **mUIClipNames;
	char **mSkinningNames;
	char **mBoneNames;
	unsigned int mNumBoneNames;
	unsigned int mNumUIClips;
	bool mShowRestPose;
	bool mShowCurrentPose;
	bool mShowBindPose;
	bool mShowMesh;
	SkinningType mSkinType;

  public:
	void Initialize();
	void Update(float deltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
	void ImGui(nk_context *inContext);
};

#endif
