#ifndef _H_REARRANGEBONES_
#define _H_REARRANGEBONES_

#include "Clip.h"
#include "Mesh.h"
#include "Skeleton.h"
#include <map>


typedef std::map<int, int> BoneMap;

// Generates BoneMap and rearranges the bind, inverse bind, and rest posts in
// the skeleton
BoneMap RearrangeSkeleton(Skeleton &skeleton);
void RearrangeMesh(Mesh &mesh, BoneMap &boneMap);
void RearrangeClip(Clip &clip, BoneMap &boneMap);
void RearrangeFastclip(FastClip &clip, BoneMap &boneMap);

#endif
