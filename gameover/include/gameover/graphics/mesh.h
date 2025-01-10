#pragma once
#include "cstdint"

namespace gameover::graphics {
	class Mesh {
	public:
		Mesh(float* vertextArray, uint32_t vertextCount, uint32_t dimensions);
		~Mesh();

		void Bind();
		void Unbind();

		inline uint32_t GetVertexCount() const { return mVertextCount; }
	private:
		uint32_t mVertextCount;
		uint32_t mVao;
		uint32_t mPositionVbo;
	};
}