#ifndef _H_POSE_
#define _H_POSE_

#include "DualQuaternion.h"
#include "Transform.h"
#include <vector>

class Pose {
  protected:
	std::vector<Transform> mJoints;
	std::vector<int> mParents;

  public:
	Pose();
	Pose(const Pose &p);
	Pose &operator=(const Pose &p);
	Pose(unsigned int numJoints);
	void Resize(unsigned int size);
	unsigned int Size();
	Transform GetLocalTransform(unsigned int index);
	void SetLocalTransform(unsigned int index, const Transform &transform);
	Transform GetGlobalTransform(unsigned int index);
	Transform operator[](unsigned int index);
	void GetMatrixPalette(std::vector<mat4> &out);
	int GetParent(unsigned int index);
	void SetParent(unsigned int index, int parent);

	bool operator==(const Pose &other);
	bool operator!=(const Pose &other);

	/*
		There are three stages in the animation pipeline where
		... it makes sense to replace matrices with dual quaternions:

		1. Convert the matrices to dual quaternions in the vertex shader.
		2. Convert the matrices of the current pose to dual quaternions,
		... then pass it to the vertex shader
		3. Convert each transform of the current pose to a dual quaternion,
		... then accumulate the world transform as dual quaternion
	*/
	void GetDualQuaternionPalette(std::vector<DualQuaternion> &out);
	DualQuaternion GetGlobalDualQuaternion(unsigned int index);
};

#endif // !_H_POSE_
