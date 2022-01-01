#ifndef _H_FRAME_
#define _H_FRAME_

template <unsigned int N> class Frame
{
  public:
    float mValue[N];
    float mIn[N];
    float mOut[N];
    float mTime;
};

typedef Frame<1U> ScalarFrame;
typedef Frame<3U> VectorFrame;
typedef Frame<4U> QuaternionFrame;

#endif
