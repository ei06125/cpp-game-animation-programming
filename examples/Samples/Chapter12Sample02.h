#ifndef _H_CHAPTER12SAMPLE02_
#define _H_CHAPTER12SAMPLE02_

#include "Application.h"
#include "Blending.h"
#include "Clip.h"
#include "CrossFadeController.h"
#include "DebugDraw.h"
#include "Mesh.h"
#include "Pose.h"
#include "SamplePoseInstance.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter12Sample02 : public Application {
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

	CrossFadeController mController;
	unsigned int mNextAnim;
	float mFadeTime;

	char **mUIClipNames;
	char **mSkinningNames;
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
