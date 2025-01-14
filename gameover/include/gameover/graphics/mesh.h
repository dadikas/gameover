#pragma once
#include "cstdint"

namespace gameover::graphics {
	class Mesh {
	public:
		Mesh(float* vertextArray, uint32_t vertextCount, uint32_t dimensions);
		Mesh(float* vertextArray, uint32_t vertextCount, uint32_t dimensions, uint32_t* elementArray, uint32_t element);

		~Mesh();

		void Bind();
		void Unbind();

		inline uint32_t GetVertexCount() const { return mVertextCount; }
		inline uint32_t GetElementCount() const { return mElementCount; }
	private:
		uint32_t mVertextCount, mElementCount;
		uint32_t mVao, mEbo;
		uint32_t mPositionVbo;
	};
}