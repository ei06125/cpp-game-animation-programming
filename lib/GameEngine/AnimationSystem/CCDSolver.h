#ifndef _H_CCDSOLVER_
#define _H_CCDSOLVER_

#include "Transform.h"
#include <vector>

/*
	CCD stands for Cyclic Coordinate Descent.
	This algorithm can be used to pose a chain of joints in a way that
	the last joint on the chain comes as close as possible to touching a target.

	There are three important concepts for CCD.
	1. Goal - the point in space you are trying to touch
	2. IK Chain - a list of all the joints that will need to rotate to reach the
   goal
	3. End Effector - the last joint in the chain
*/
class CCDSolver {
  protected:
	// IKChain has a parent-child relationship; 0 is the root node; Transform is
	// in local space
	std::vector<Transform> mIKChain;
	unsigned int mNumSteps;
	// A delta to control how close the target has to be for the chain to be
	// considered solved
	float mThreshold;

  public:
	CCDSolver();
	unsigned int Size();
	void Resize(unsigned int newSize);

	Transform &operator[](unsigned int index);
	// Returns a concatenation of Transforms from index to root (parents)
	Transform GetGlobalTransform(unsigned int index);

	unsigned int GetNumSteps();
	void SetNumSteps(unsigned int numSteps);

	float GetThreshold();
	void SetThreshold(float value);
	// Returns true if the chain was solved
	bool Solve(const Transform &target);
};

#endif
