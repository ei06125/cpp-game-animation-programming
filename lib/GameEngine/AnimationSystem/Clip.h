#ifndef _H_CLIP_
#define _H_CLIP_

#include "TransformTrack.h"
#include <string>
#include <vector>

class Pose;

template <typename TRACK> class TClip
{
  protected:
    std::vector<TRACK> mTracks;
    std::string mName;
    float mStartTime;
    float mEndTime;
    bool mLooping;

  protected:
    float AdjustTimeToFitRange(float inTime);

  public:
    TClip();
    unsigned int GetIdAtIndex(unsigned int index);
    void SetIdAtIndex(unsigned int index, unsigned int id);
    unsigned int Size();
    float Sample(Pose &outPose, float inTime);
    TRACK &operator[](unsigned int index);
    /**
     * @brief called from the code that loads the animation clip
     */
    void RecalculateDuration();
    std::string &GetName();
    void SetName(const std::string &inNewName);
    float GetDuration();
    float GetStartTime();
    float GetEndTime();
    bool GetLooping();
    void SetLooping(bool inLooping);
};

typedef TClip<TransformTrack> Clip;
typedef TClip<FastTransformTrack> FastClip;

FastClip OptimizeClip(Clip &input);

#endif
