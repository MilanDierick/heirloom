// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_APPLICATIONEVENTARGS_H
#define HEIRLOOM_APPLICATIONEVENTARGS_H

#include "Event.h"

namespace Heirloom
{
	struct WindowResizedEventArgs : EventArgs
	{
		[[nodiscard]] WindowResizedEventArgs(const unsigned width, const unsigned height)
				: Width(width),
				  Height(height)
		{
		}

		unsigned int Width, Height;
	};

	struct WindowClosedEventArgs : EventArgs
	{
	};

	struct AppTickEventArgs : EventArgs
	{
	};

	struct AppUpdatedEventArgs : EventArgs
	{
	};

	struct AppRenderEventArgs : EventArgs
	{
	};
}

#endif //HEIRLOOM_APPLICATIONEVENTARGS_H
