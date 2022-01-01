#ifndef _H_ANIMBAKER_
#define _H_ANIMBAKER_

#include "Clip.h"

// Forward Declarations
class AnimTexture;
class Skeleton;

void BakeAnimationToTexture(Skeleton &skel, Clip &clip, AnimTexture &tex);

#endif
