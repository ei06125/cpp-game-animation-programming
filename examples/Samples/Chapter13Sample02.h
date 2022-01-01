#ifndef _H_CHAPTER13SAMPLE02_
#define _H_CHAPTER13SAMPLE02_

#include "DebugDraw.h"
#include "FABRIKSolver.h"
#include "Application.h"
#include <vector>

class Chapter13Sample02 : public Application
{
  protected:
    Transform mTarget;
    FABRIKSolver mSolver;
    DebugDraw *mCCDLines;
    DebugDraw *mCCDPoints;
    DebugDraw *mTargetVisual[3];
    float mCamPitch;
    float mCamYaw;
    float mCamDist;

  public:
    void Initialize();
    void Update(float deltaTime);
    void Render(float inAspectRatio);
    void Shutdown();
    void ImGui(nk_context *inContext);
};

#endif
