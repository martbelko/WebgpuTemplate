#pragma once

#include "Base/Window.h"
#include "Base/Timestep.h"

int main(int argc, char* argv[]);

namespace Base {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Update(Timestep ts) = 0;
		virtual void Render() = 0;
		virtual void RenderImGui() = 0;
	private:
		void Run();
		void OnFrame(Timestep ts);
	private:
#if defined(SS_PLATFORM_WEB)
		static int EMSRedraw(double time, void* userData);
#endif
	private:
		Window* m_Window;
		bool m_Running = false;
	private:
		friend int ::main(int argc, char* argv[]);
	};

}
