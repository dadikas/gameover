#include "gameover/graphics/rendercommands.h"
#include "gameover/log.h"

#include "gameover/graphics/mesh.h"
#include "gameover/graphics/shader.h"

#include "glad/glad.h"

namespace gameover::graphics::rendercommands {

	void RenderMesh::Excute() {
		std::shared_ptr<Mesh> mesh = mMesh.lock();
		std::shared_ptr<Shader> shader = mShader.lock();

		if (mesh && shader) {
			mesh->Bind();
			shader->Bind();

			if (mesh->GetElementCount() > 0) {
				glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0);
			}
			else {
				glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());

			}


			shader->Unbind();
			mesh->Unbind();
		}
		else {
			GAMEOVER_WARN("Attemping to excute RenderMesh with invalid value")
		}
	}
}