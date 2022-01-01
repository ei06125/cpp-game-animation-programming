#ifndef _H_DUALQUATERNION_
#define _H_DUALQUATERNION_

#include "Transform.h"
#include "quat.h"

struct DualQuaternion {
  union {
    struct {
      quat real; // rotation data
      quat dual; // position data
    };
    float v[8];
  };

  // The identity dual quaternion has identity in real part and zero in dual
  // part
  inline DualQuaternion() : real(0, 0, 0, 1), dual(0, 0, 0, 0) {}
  inline DualQuaternion(const quat &r, const quat &d) : real(r), dual(d) {}
};

DualQuaternion operator+(const DualQuaternion &l, const DualQuaternion &r);
DualQuaternion operator*(const DualQuaternion &dq, float f);

// Multiplication order is left to right
// Left to right is the OPPOSITE of matrices and quaternions
DualQuaternion operator*(const DualQuaternion &l, const DualQuaternion &r);

bool operator==(const DualQuaternion &l, const DualQuaternion &r);
bool operator!=(const DualQuaternion &l, const DualQuaternion &r);

/*
    The dot product measures how similar two dual quaternions are.
    It is positive if the dual quaternions point in the same direction.
    It is negative if the dual quaternions point in opposite directions.
    It is zero if the dual quaternions are prependicular.
*/
float dot(const DualQuaternion &l, const DualQuaternion &r);
DualQuaternion conjugate(const DualQuaternion &dq);

/*
    Normalizing a dual quaternion is like normalizing a regular quaternion,
    ... operating mainly on the real part.

    If a dual quaternion changes over time,
    ... it might become non-normalized due to a floating-point error.
    Instead of checking the lenght against 1, which involves a sqrt(),
    ... check if the square(length) is 1, which is much faster,
    ... and if not, normalize it.
*/
DualQuaternion normalized(const DualQuaternion &dq);
void normalize(DualQuaternion &dq);

// The resulting dual quaternion does not need to be normalized
DualQuaternion transformToDualQuat(const Transform &t);
Transform dualQuatToTransform(const DualQuaternion &dq);

vec3 transformVector(const DualQuaternion &dq, const vec3 &v);
vec3 transformPoint(const DualQuaternion &dq, const vec3 &v);

#endif // !_H_DUALQUATERNION_
