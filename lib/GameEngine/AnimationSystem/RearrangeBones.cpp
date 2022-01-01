#include "RearrangeBones.h"
#include <list>

BoneMap RearrangeSkeleton(Skeleton &skeleton) {
	Pose &restPose = skeleton.GetRestPose();
	Pose &bindPose = skeleton.GetBindPose();

	// Make sure the skeleton is valid
	unsigned int size = restPose.Size();
	if (size == 0) {
		return BoneMap();
	}

	// Each element of the outer vector represents one bone
	// ... and the indices of this vector and the mJoints array in the bind or
	// rest poses are parallel Each element of the inner vector represents a
	// child
	// ... that the joint at the index of the outer vector contains
	std::vector<std::vector<int>> hierarchy(size);
	// This list will be used later to traverse the map depth
	std::list<int> process;
	for (unsigned int i = 0; i < size; ++i) {
		int parent = restPose.GetParent(i);
		// If a joint has a parent, add the index to the parent's vector of
		// children
		if (parent >= 0) {
			hierarchy[parent].push_back((int)i);
		}
		// ... otherwise, add it directly to the process list
		else {
			process.push_back((int)i);
		}
	}

	// Configuration maps (new > old, and old > new)
	BoneMap mapForward;
	BoneMap mapBackward;
	int index = 0;
	while (process.size() > 0) {
		int current = *process.begin();
		process.pop_front();
		std::vector<int> &children = hierarchy[current];

		unsigned int numChildren = (unsigned int)children.size();
		for (unsigned int i = 0; i < numChildren; ++i) {
			process.push_back(children[i]);
		}

		// The current index of the forward map is an atomic counter (?)
		mapForward[index] = current;
		mapBackward[current] = index;
		index += 1;
	}

	// Add null node on both maps
	mapForward[-1] = -1;
	mapBackward[-1] = -1;

	// Build new rest and bind poses with bones in the correct order
	Pose newRestPose(size);
	Pose newBindPose(size);
	std::vector<std::string> newNames(size);
	for (unsigned int i = 0; i < size; ++i) {
		int thisBone = mapForward[i];
		newRestPose.SetLocalTransform(i, restPose.GetLocalTransform(thisBone));
		newBindPose.SetLocalTransform(i, bindPose.GetLocalTransform(thisBone));
		newNames[i] = skeleton.GetJointName(thisBone);

		int parent = mapBackward[bindPose.GetParent(thisBone)];
		newRestPose.SetParent(i, parent);
		newBindPose.SetParent(i, parent);
	}

	skeleton.Set(newRestPose, newBindPose, newNames);
	return mapBackward;
} // End of RearrangeSkeleton function

void RearrangeClip(Clip &clip, BoneMap &boneMap) {
	unsigned int size = clip.Size();

	for (unsigned int i = 0; i < size; ++i) {
		int joint = (int)clip.GetIdAtIndex(i);
		unsigned int newJoint = (unsigned int)boneMap[joint];
		clip.SetIdAtIndex(i, newJoint);
	}
}

void RearrangeFastclip(FastClip &clip, BoneMap &boneMap) {
	unsigned int size = clip.Size();

	for (unsigned int i = 0; i < size; ++i) {
		int joint = (int)clip.GetIdAtIndex(i);
		unsigned int newJoint = (unsigned int)boneMap[joint];
		clip.SetIdAtIndex(i, newJoint);
	}
}

void RearrangeMesh(Mesh &mesh, BoneMap &boneMap) {
	std::vector<ivec4> &influences = mesh.GetInfluences();
	unsigned int size = (unsigned int)influences.size();

	for (unsigned int i = 0; i < size; ++i) {
		influences[i].x = boneMap[influences[i].x];
		influences[i].y = boneMap[influences[i].y];
		influences[i].z = boneMap[influences[i].z];
		influences[i].w = boneMap[influences[i].w];
	}

	mesh.UpdateOpenGLBuffers();
}
