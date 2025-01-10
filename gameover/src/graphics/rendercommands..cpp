#include "graphics/rendercommands.h"
#include "log.h"

#include "graphics/mesh.h"
#include "graphics/shader.h"

#include "glad/glad.h"

namespace gameover::graphics::rendercommands {

	void RenderMesh::Excute() {
		std::shared_ptr<Mesh> mesh = mMesh.lock();
		std::shared_ptr<Shader> shader = mShader.lock();

		if (mesh && shader) {
			mesh->Bind();
			shader->Bind();

			glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());

			shader->Unbind();
			mesh->Unbind();
		}
		else {
			GAMEOVER_WARN("Attemping to excute RenderMesh with invalid value")
		}
	}
}