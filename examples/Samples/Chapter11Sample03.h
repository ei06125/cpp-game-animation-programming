#ifndef _H_CHAPTER11SAMPLE03_
#define _H_CHAPTER11SAMPLE03_

#include "Application.h"
#include "AnimationSystem/DebugDraw.h"
#include <vector>
#include "AnimationSystem/Pose.h"
#include "AnimationSystem/Clip.h"
#include "AnimationSystem/Skeleton.h"
#include "RendererEngine/Mesh.h"
#include "RendererEngine/Texture.h"
#include "AnimationSystem/SkinningType.h"
#include <vector>

class Chapter11Sample03 : public Application {
protected:
	Texture* mDiffuseTexture;
	Shader* mStaticShader;
	Shader* mSkinnedShader;
	std::vector<Mesh> mMeshes;
	std::vector<mat4> mPosePalette;
	Skeleton mSkeleton;
	Pose mCurrentPose;
	std::vector<Clip> mClips;
	unsigned int mCurrentClip;
	float mPlaybackTime;
	DebugDraw* mBindPoseVisual;
	DebugDraw* mRestPoseVisual;
	DebugDraw* mCurrentPoseVisual;

	char** mUIClipNames;
	char** mSkinningNames;
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
	void ImGui(nk_context* inContext);
};

#endif