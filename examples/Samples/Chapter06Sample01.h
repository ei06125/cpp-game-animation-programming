#ifndef _H_CHAPTER06_SAMPLE01_
#define _H_CHAPTER06_SAMPLE01_

#include "Application.h"
#include "Attribute.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "vec2.h"
#include "vec3.h"

class Chapter06Sample01 : public Application {
  protected:
	Shader *mShader;
	Attribute<vec3> *mVertexPositions;
	Attribute<vec3> *mVertexNormals;
	Attribute<vec2> *mVertexTexCoords;
	IndexBuffer *mIndexBuffer;
	Texture *mDisplayTexture;
	float mRotation;

  public:
	void Initialize();
	void Update(float inDeltaTime);
	void Render(float inAspectRatio);
	void Shutdown();
};

#endif
