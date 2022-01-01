#include "CCDSolver.h"

CCDSolver::CCDSolver() {
	mNumSteps = 15;
	mThreshold = 0.00001f;
}

unsigned int CCDSolver::Size() { return mIKChain.size(); }

void CCDSolver::Resize(unsigned int newSize) { mIKChain.resize(newSize); }

Transform &CCDSolver::operator[](unsigned int index) { return mIKChain[index]; }

unsigned int CCDSolver::GetNumSteps() { return mNumSteps; }

void CCDSolver::SetNumSteps(unsigned int numSteps) { mNumSteps = numSteps; }

float CCDSolver::GetThreshold() { return mThreshold; }

void CCDSolver::SetThreshold(float value) { mThreshold = value; }

Transform CCDSolver::GetGlobalTransform(unsigned int index) {
	unsigned int size = (unsigned int)mIKChain.size();
	Transform world = mIKChain[index];
	for (int i = (int)index - 1; i >= 0; --i) {
		world = combine(mIKChain[i], world);
	}
	return world;
}

bool CCDSolver::Solve(const Transform &target) {
	// Make sure the chain is valid
	unsigned int size = Size();
	if (size == 0) {
		return false;
	}

	unsigned int last = size - 1;
	float thresholdSq = mThreshold * mThreshold;

	// cache the goal position
	vec3 goal = target.position;

	for (unsigned int i = 0; i < mNumSteps; ++i) {
		vec3 effector = GetGlobalTransform(last).position;
		// Return early if close enough
		if (lenSq(goal - effector) < thresholdSq) {
			return true;
		}

		// Start at size-2 because size-1 is the last element and
		// ... rotating the last element has no effect on any bones
		for (int j = (int)size - 2; j >= 0; --j) {
			// -> APPLY CONSTRAINTS HERE!

			effector = GetGlobalTransform(last).position;

			Transform world = GetGlobalTransform(j);

			// Find the vectors (jointToEffector and jointToGoal)
			vec3 position = world.position;
			vec3 toEffector = effector - position;
			vec3 toGoal = goal - position;

			// Find the quaternion that matches the previous vectors
			quat effectorToGoal;
			if (lenSq(toGoal) > 0.00001f) {
				effectorToGoal = fromTo(toEffector, toGoal);
			}

			quat rotation = world.rotation;
			// put into world space with correct orientation
			quat worldRotated = rotation * effectorToGoal;
			// Multiply by the inverse to put back into the joint space
			quat localRotate = worldRotated * inverse(rotation);
			mIKChain[j].rotation = localRotate * mIKChain[j].rotation;

			// Return early if close enough
			effector = GetGlobalTransform(last).position;
			if (lenSq(goal - effector) < thresholdSq) {
				return true;
			}
		}
	}

	return false;
} // End CCDSolver::Solve function
