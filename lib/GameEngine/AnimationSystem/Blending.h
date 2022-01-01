#ifndef _H_BLENDING_
#define _H_BLENDING_

#include "Clip.h"
#include "Pose.h"


class Skeleton;

bool IsInHierarchy(Pose &pose, unsigned int parent, unsigned int search);
void Blend(Pose &output, Pose &a, Pose &b, float t, int blendroot);

/**
 * @brief Samples the additive clip at time 0 into an output pose
 * This output pose is the reference that is used to add two poses together
 */
Pose MakeAdditivePose(Skeleton &skeleton, Clip &clip);

/**
 * @brief Performs additive blending between two poses.
 * The additive blending formula is "result pose = input pose + (additive pose -
 * additive base pose)" This function is intended to be called during
 * initialization time.
 */
void Add(Pose &output, Pose &inPose, Pose &addPose, Pose &additiveBasePose,
		 int blendroot);

#endif
