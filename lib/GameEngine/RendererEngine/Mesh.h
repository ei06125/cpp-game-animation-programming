#ifndef _H_MESH_
#define _H_MESH_

#include <vector>

// forward declarations
class Pose;
class Skeleton;
#include "mat4.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
template <typename T> class Attribute;
class IndexBuffer;

class Mesh {
  protected:
	std::vector<vec3> mPosition;
	std::vector<vec3> mNormal;
	std::vector<vec2> mTexCoord;
	std::vector<vec4> mWeights;
	std::vector<ivec4> mInfluences;
	std::vector<unsigned int> mIndices;

  protected:
	Attribute<vec3> *mPosAttrib;
	Attribute<vec3> *mNormAttrib;
	Attribute<vec2> *mUvAttrib;
	Attribute<vec4> *mWeightAttrib;
	Attribute<ivec4> *mInfluenceAttrib;
	IndexBuffer *mIndexBuffer;

  protected:
	// Additional copy of the pose and normal data, as well as matrix palette
	// for CPU skinning
	std::vector<vec3> mSkinnedPosition;
	std::vector<vec3> mSkinnedNormal;
	std::vector<mat4> mPosePalette;

  public:
	Mesh();
	Mesh(const Mesh &);
	Mesh &operator=(const Mesh &);
	~Mesh();
	std::vector<vec3> &GetPosition();
	std::vector<vec3> &GetNormal();
	std::vector<vec2> &GetTexCoord();
	std::vector<vec4> &GetWeights();
	std::vector<ivec4> &GetInfluences();
	std::vector<unsigned int> &GetIndices();

	void UpdateOpenGLBuffers(); // syncs the vectors holding data to the GPU
	void Bind(int position, int normal, int texCoord, int weight,
			  int influcence);
	void Draw();
	void DrawInstanced(unsigned int numInstances);
	void UnBind(int position, int normal, int texCoord, int weight,
				int influcence);

	friend void SkinOnCPU(Skeleton &skeleton, Pose &pose, Mesh &mesh);
	friend void SkinOnCPU(std::vector<mat4> &animatedPose, Mesh &mesh);
};

#endif // !_H_MESH_
