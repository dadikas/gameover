#pragma once
#include <memory>

namespace gameover::graphics {
	class Mesh;
	class Shader;
	namespace rendercommands {
		class Rendercommand {
		public:
			virtual void Excute() = 0;
			virtual ~Rendercommand() {};
		};

		class RenderMesh : public Rendercommand {
		public:
			RenderMesh(std::weak_ptr<Mesh> mesh, std::weak_ptr<Shader> shader):mMesh(mesh), mShader(shader){}
			virtual void Excute();
		private:
			std::weak_ptr<Mesh> mMesh;
			std::weak_ptr<Shader> mShader;
		};
	}
}