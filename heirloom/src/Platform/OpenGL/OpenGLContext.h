//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_OPENGLCONTEXT_H
#define HEIRLOOM_OPENGLCONTEXT_H

#include "Heirloom/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Heirloom
{
	class OpenGLContext final : public GraphicsContext
	{
	public:
		explicit OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}

#endif //HEIRLOOM_OPENGLCONTEXT_H
