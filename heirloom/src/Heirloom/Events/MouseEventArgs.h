// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_MOUSEEVENTARGS_H
#define HEIRLOOM_MOUSEEVENTARGS_H

#include "Event.h"
#include "Heirloom/Core/MouseCodes.h"

namespace Heirloom
{
	struct MouseMovedEventArgs : EventArgs
	{
		[[nodiscard]] MouseMovedEventArgs(const float mouseX, const float mouseY)
				: MouseX(mouseX),
				  MouseY(mouseY)
		{
		}

		float MouseX, MouseY;
	};

	struct MouseScrolledEventArgs : EventArgs
	{
		[[nodiscard]] MouseScrolledEventArgs(const float xOffset, const float yOffset)
				: XOffset(xOffset),
				  YOffset(yOffset)
		{
		}

		float XOffset, YOffset;
	};

	struct MouseButtonPressedEventArgs : EventArgs
	{
		[[nodiscard]] explicit MouseButtonPressedEventArgs(const MouseCode button)
				: Button(button)
		{
		}

		MouseCode Button;
	};

	struct MouseButtonReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit MouseButtonReleasedEventArgs(const MouseCode button)
				: Button(button)
		{
		}

		MouseCode Button;
	};
}

#endif //HEIRLOOM_MOUSEEVENTARGS_H
