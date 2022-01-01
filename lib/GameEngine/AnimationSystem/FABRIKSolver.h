#ifndef _H_FABRIKSOLVER_
#define _H_FABRIKSOLVER_

#include "Transform.h"
#include <vector>

/*
	FABRIK stands for Forward And Backward Reaching Inverse Kinematics.
	This algorithm can be used to pose a chain of joints in a way that
	the last joint on the chain comes as close as possible to touching a target.

	FABRIK has a more natural humanoid looking convergence.
	FABRIK works with positions instead of rotations.
	FABRIK tends to converge faster.
	FABRIK needs pre and post process to convert rotations from/to vectors
*/

class FABRIKSolver {
  protected:
	// IKChain has a parent-child relationship; 0 is the root node; Transform is
	// in local space
	std::vector<Transform> mIKChain;
	unsigned int mNumSteps;
	// A delta to control how close the target has to be for the chain to be
	// considered solved
	float mThreshold;
	// These vectors are needed because FABRIK does not take rotations into
	// account
	std::vector<vec3> mWorldChain;
	std::vector<float>
		mLengths; // stores the distance from a joint to its parent

  protected:
	void IKChainToWorld();
	void IterateForward(const vec3 &goal);
	void IterateBackward(const vec3 &base);
	void WorldToIKChain();

  public:
	FABRIKSolver();

	unsigned int Size();
	void Resize(unsigned int newSize);

	Transform GetLocalTransform(unsigned int index);
	void SetLocalTransform(unsigned int index, const Transform &t);

	// ? Not in the book //Transform& operator[](unsigned int index);
	// Returns a concatenation of Transforms from index to root (parents)
	Transform GetGlobalTransform(unsigned int index);

	unsigned int GetNumSteps();
	void SetNumSteps(unsigned int numSteps);

	float GetThreshold();
	void SetThreshold(float value);

	// Returns true if the chain was solved
	bool Solve(const Transform &target);
};

#endif // !_H_FABRIKSOLVER_
