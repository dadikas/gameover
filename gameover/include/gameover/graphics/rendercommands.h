#pragma once
#include <memory>

namespace gameover::graphics {
	class Mesh;
	class Shader;
	class Framebuffer;
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

		class PushFramebuffer : public Rendercommand {
		public:
			PushFramebuffer(std::weak_ptr<Framebuffer> framebuffer): mFramebuffer(framebuffer){}
			virtual void Excute() override;
		private:
			std::weak_ptr<Framebuffer> mFramebuffer;
		};
		class PopFramebuffer : public Rendercommand {
		public:
			PopFramebuffer(){}
			virtual void Excute() override;
		};
	}
}