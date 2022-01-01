#include "AnimBaker.h"

#include "AnimTexture.h"
#include "Clip.h"
#include "Skeleton.h"

void BakeAnimationToTexture(Skeleton &skel, Clip &clip, AnimTexture &tex) {
	Pose &bindPose = skel.GetBindPose();

	// Create a pose that the animation will be sampled into
	Pose samplePose = bindPose;

	// Loop across the x dimensino of the texture, which is time
	unsigned int texWidth = tex.Size();
	for (unsigned int x = 0; x < texWidth; ++x) {
		// Find the normalized value of the iterator
		float t = (float)x / (float)(texWidth - 1);
		float time = clip.GetStartTime() + clip.GetDuration() * t;
		// Sample the clip at `time` for the current pixel
		clip.Sample(samplePose, time);

		// Loop through all the joints in the bind pose
		for (unsigned int y = 0; y < bindPose.Size() * 3; y += 3) {
			// Find the global transform of the current joint
			Transform transform = samplePose.GetGlobalTransform(y / 3);
			tex.SetTexel(x, y + 0, transform.position);
			tex.SetTexel(x, y + 1, transform.rotation);
			tex.SetTexel(x, y + 2, transform.scale);
		}
	}
	// Make the texture usable after baking
	tex.UploadTextureDataToGPU();
}
