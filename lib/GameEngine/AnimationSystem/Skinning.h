#ifndef _H_SKINNING_
#define _H_SKINNING_

#include <vector>

#include "Attribute.h"
#include "Mesh.h"
#include "Pose.h"
#include "Skeleton.h"
#include "mat4.h"

void SkinOnCPU(Skeleton &skeleton, Pose &pose, Mesh &mesh);

void SkinOnCPU(std::vector<mat4> &animatedPose, Mesh &mesh);

#endif // !_H_SKINNING_
