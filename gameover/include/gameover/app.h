#pragma once
namespace gameover {
	class App {
	public:
		App(){}
		~App(){}

		virtual void Initialize(){}
		virtual void Shutdown(){}

		virtual void Update(){}
		virtual void Render(){}

	private:
	};
}