#ifndef _H_CHAPTER13SAMPLE03_
#define _H_CHAPTER13SAMPLE03_

#include "Application.h"
#include "Clip.h"
#include "DebugDraw.h"
#include "IKLeg.h"
#include "Intersections.h"
#include "Mesh.h"
#include "Pose.h"
#include "Skeleton.h"
#include "SkinningType.h"
#include "Texture.h"
#include <vector>

class Chapter13Sample03 : public Application {
  protected:
	Texture *mCourseTexture;
	std::vector<Mesh> mIKCourse;
	std::vector<Triangle> mTriangles;

	VectorTrack mMotionTrack;
	float mWalkingTime;

	Transform mModel;
	std::vector<Mesh> mMeshes;
	Pose mCurrentPose;
	std::vector<mat4> mPosePalette;
	float mSinkIntoGround;

	IKLeg *mLeftLeg;
	IKLeg *mRightLeg;
	float mToeLength;
	float mLastModelY;

	Texture *mDiffuseTexture;
	Shader *mStaticShader;
	Shader *mSkinnedShader;
	Skeleton mSkeleton;
	std::vector<Clip> mClips;
	unsigned int mCurrentClip;
	float mPlaybackTime;
	DebugDraw *mCurrentPoseVisual;

	bool mShowIKPose;
	bool mShowCurrentPose;
	float mTimeMod;
	bool mDepthTest;
	bool mShowMesh;
	bool mShowEnvironment;

  public:
	void Initialize();
	void Update(float deltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
	void ImGui(nk_context *inContext);
};

#endif
