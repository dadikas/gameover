#include "graphics/mesh.h"

#include "glad/glad.h"

namespace gameover::graphics {
	Mesh::Mesh(float* vertextArray, uint32_t vertextCount, uint32_t dimensions)
		:mVertextCount(vertextCount)
	{
		glGenVertexArrays(1, &mVao);
		glBindVertexArray(mVao);

		glGenBuffers(1, &mPositionVbo);
		glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo);
		glBufferData(GL_ARRAY_BUFFER, vertextCount * dimensions * sizeof(float), vertextArray, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		glBindVertexArray(0);
	}
	Mesh::~Mesh() {
		glDeleteBuffers(1, &mPositionVbo);
		glDeleteVertexArrays(1, &mVao);
	}

	void Mesh::Bind() {
		glBindVertexArray(mVao);
		glEnableVertexAttribArray(0);
	}

	void Mesh::Unbind() {
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}