#include "Skinning.h"

#if 1
void SkinOnCPU(Skeleton &skeleton, Pose &pose, Mesh &mesh) {

	unsigned int numVerts = (unsigned int)mesh.mPosition.size();
	if (numVerts == 0) {
		return;
	}

	mesh.mSkinnedPosition.resize(numVerts);
	mesh.mSkinnedNormal.resize(numVerts);

	pose.GetMatrixPalette(mesh.mPosePalette);
	std::vector<mat4> invPosePalette = skeleton.GetInvBindPose();

	for (unsigned int i = 0; i < numVerts; ++i) {
		ivec4 &j = mesh.mInfluences[i];
		vec4 &w = mesh.mWeights[i];

		// Build a skin matrix
		// ... The vertex should be transformed by the inverse bind pose first
		// ... With right-to-left multiplication, this puts inverse bind pose on
		// the right
		mat4 m0 = (mesh.mPosePalette[j.x] * invPosePalette[j.x]) * w.x;
		mat4 m1 = (mesh.mPosePalette[j.y] * invPosePalette[j.y]) * w.y;
		mat4 m2 = (mesh.mPosePalette[j.z] * invPosePalette[j.z]) * w.z;
		mat4 m3 = (mesh.mPosePalette[j.w] * invPosePalette[j.w]) * w.w;

		mat4 skin = m0 + m1 + m2 + m3;

		mesh.mSkinnedPosition[i] = transformPoint(skin, mesh.mPosition[i]);
		mesh.mSkinnedNormal[i] = transformVector(skin, mesh.mNormal[i]);
	}

	mesh.mPosAttrib->Set(mesh.mSkinnedPosition);
	mesh.mNormAttrib->Set(mesh.mSkinnedNormal);
}

// a skinning method that respects the pre-multiplied skin matrix
void SkinOnCPU(std::vector<mat4> &animatedPose, Mesh &mesh) {

	unsigned int numVerts = (unsigned int)mesh.mPosition.size();
	if (numVerts == 0) {
		return;
	}

	mesh.mSkinnedPosition.resize(numVerts);
	mesh.mSkinnedNormal.resize(numVerts);

	for (unsigned int i = 0; i < numVerts; ++i) {
		ivec4 &j = mesh.mInfluences[i];
		vec4 &w = mesh.mWeights[i];

		vec3 p0 = transformPoint(animatedPose[j.x], mesh.mPosition[i]);
		vec3 p1 = transformPoint(animatedPose[j.y], mesh.mPosition[i]);
		vec3 p2 = transformPoint(animatedPose[j.z], mesh.mPosition[i]);
		vec3 p3 = transformPoint(animatedPose[j.w], mesh.mPosition[i]);
		mesh.mSkinnedPosition[i] = p0 * w.x + p1 * w.y + p2 * w.z + p3 * w.w;

		vec3 n0 = transformVector(animatedPose[j.x], mesh.mNormal[i]);
		vec3 n1 = transformVector(animatedPose[j.y], mesh.mNormal[i]);
		vec3 n2 = transformVector(animatedPose[j.z], mesh.mNormal[i]);
		vec3 n3 = transformVector(animatedPose[j.w], mesh.mNormal[i]);
		mesh.mSkinnedNormal[i] = n0 * w.x + n1 * w.y + n2 * w.z + n3 * w.w;
	}

	mesh.mPosAttrib->Set(mesh.mSkinnedPosition);
	mesh.mNormAttrib->Set(mesh.mSkinnedNormal);
}

#else
void Mesh::CPUSkin(Skeleton &skeleton, Pose &pose, Mesh &mesh) {
	unsigned int numVerts = (unsigned int)mesh.mPosition.size();
	if (numVerts == 0) {
		return;
	}

	mesh.mSkinnedPosition.resize(numVerts);
	mesh.mSkinnedNormal.resize(numVerts);
	Pose &bindPose = skeleton.GetBindPose();

	for (unsigned int i = 0; i < numVerts; ++i) {
		ivec4 &joint = mesh.mInfluences[i];
		vec4 &weight = mesh.mWeights[i];

		Transform skin0 = combine(pose[joint.x], inverse(bindPose[joint.x]));
		vec3 p0 = transformPoint(skin0, mesh.mPosition[i]);
		vec3 n0 = transformVector(skin0, mesh.mNormal[i]);

		Transform skin1 = combine(pose[joint.y], inverse(bindPose[joint.y]));
		vec3 p1 = transformPoint(skin1, mesh.mPosition[i]);
		vec3 n1 = transformVector(skin1, mesh.mNormal[i]);

		Transform skin2 = combine(pose[joint.z], inverse(bindPose[joint.z]));
		vec3 p2 = transformPoint(skin2, mesh.mPosition[i]);
		vec3 n2 = transformVector(skin2, mesh.mNormal[i]);

		Transform skin3 = combine(pose[joint.w], inverse(bindPose[joint.w]));
		vec3 p3 = transformPoint(skin3, mesh.mPosition[i]);
		vec3 n3 = transformVector(skin3, mesh.mNormal[i]);

		mesh.mSkinnedPosition[i] =
			p0 * weight.x + p1 * weight.y + p2 * weight.z + p3 * weight.w;
		mesh.mSkinnedNormal[i] =
			n0 * weight.x + n1 * weight.y + n2 * weight.z + n3 * weight.w;
	}

	mesh.mPosAttrib->Set(mesh.mSkinnedPosition);
	mesh.mNormAttrib->Set(mesh.mSkinnedNormal);
}
#endif
