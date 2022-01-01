///*
//    UNKNOWN IMPLEMENTATION REFERENCE (in the book)
//*/
//
//
//#include "Constraints.h"
//
//#include "Transform.h"
//#include "quat.h"
//#include <vector>
//
//Transform GetWorldTransform(unsigned int i)
//{
//}
//
//void ApplyBallSocketConstraint(int i, float limit)
//{
//    Transform mOffset;
//    quat parentRot = i == 0 ? mOffset.rotation : GetWorldTransform(i - 1).rotation;
//    quat thisRot = GetWorldTransform(i).rotation;
//
//    vec3 parentDir = parentRot * vec3(0, 0, 1);
//    vec3 thisDir = thisRot * vec3(0, 0, 1);
//    float angle = ::angle(parentDir, thisDir);
//
//    std::vector<Transform> mChain;
//    if (angle > limit * QUAT_DEG2RAD)
//    {
//        vec3 correction = cross(parentDir, thisDir);
//        quat worldspaceRotation = parentRot * angleAxis(limit * QUAT_DEG2RAD, correction);
//        mChain[i].rotation = worldspaceRotation * inverse(parentRot);
//    }
//}
//
//void ApplyHingeSocketConstraint(int i, vec3 axis)
//{
//    Transform joint = GetWorldTransform(i);
//    Transform parent = GetWorldTransform(i - 1);
//
//    vec3 currentHinge = joint.rotation * axis;
//    vec3 desiredHinge = parent.rotation * axis;
//
//    std::vector<Transform> mChain;
//    mChain[i].rotation = mChain[i].rotation * fromTo(currentHinge, desiredHinge);
//}
