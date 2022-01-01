#ifndef _H_CROSSFADECONTROLLER_
#define _H_CROSSFADECONTROLLER_

#include "CrossFadeTarget.h"
#include "Skeleton.h"
#include <vector>

/**
 * Default Special Member Functions (ctor,etc..) are OK, because even thou
 * CrossFadeController and CrossFadeTarget classes contain pointers to animation
 * clips, they don't own them
 */

class CrossFadeController {
  protected:
	// The entire list is evaluated with every frame
	std::vector<CrossFadeTarget> mTargets;
	Clip *mClip;
	float mTime;
	Pose mPose;
	Skeleton mSkeleton;
	bool mWasSkeletonSet;

  public:
	CrossFadeController();
	CrossFadeController(Skeleton &skeleton);
	void SetSkeleton(Skeleton &skeleton);
	// Set current animation
	void Play(Clip *target);
	void FadeTo(Clip *target, float fadeTime);
	void Update(float dt);
	Pose &GetCurrentPose();
	Clip *GetcurrentClip();
};

#endif
