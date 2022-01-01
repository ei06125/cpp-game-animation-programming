#ifndef _H_SKELETON_
#define _H_SKELETON_

#include "DualQuaternion.h"
#include "Pose.h"
#include "mat4.h"
#include <string>
#include <vector>


/**
 * The Skeleton class works as a helper class that manages ...
 * ... the bind pose, inverse bind pose, rest pose, and joint names.
 * The skeleton is shared by many characters, each with a unique animated pose.
 */
class Skeleton {
  protected:
	Pose mRestPose;
	Pose mBindPose;
	std::vector<mat4> mInvBindPose;
	std::vector<std::string> mJointNames;

  protected:
	void UpdateInverseBindPose();

  public:
	Skeleton();
	Skeleton(const Pose &rest, const Pose &bind,
			 const std::vector<std::string> &names);

	void Set(const Pose &rest, const Pose &bind,
			 const std::vector<std::string> &names);

	Pose &GetBindPose();
	Pose &GetRestPose();
	std::vector<mat4> &GetInvBindPose();
	std::vector<std::string> &GetJointNames();
	std::string &GetJointName(unsigned int index);

	void GetInvBindPose(std::vector<DualQuaternion> &outInvBndPose);
};

#endif
