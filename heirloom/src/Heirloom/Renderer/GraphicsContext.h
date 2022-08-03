//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_GRAPHICSCONTEXT_H
#define HEIRLOOM_GRAPHICSCONTEXT_H

namespace Heirloom
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif //HEIRLOOM_GRAPHICSCONTEXT_H
