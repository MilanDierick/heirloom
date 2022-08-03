// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_INPUT_H
#define HEIRLOOM_INPUT_H

#include "Heirloom/Core/KeyCodes.h"
#include "Heirloom/Events/Event.h"
#include "Heirloom/Events/KeyEventArgs.h"
#include "Heirloom/Events/MouseEventArgs.h"

namespace Heirloom
{
	class Input final
	{
	public:
		static Event<KeyPressedEventArgs> KeyPressedEvent;
		static Event<KeyReleasedEventArgs> KeyReleasedEvent;
		static Event<KeyTypedEventArgs> KeyTypedEvent;
		static Event<MouseButtonPressedEventArgs> MouseButtonPressedEvent;
		static Event<MouseButtonReleasedEventArgs> MouseButtonReleasedEvent;
		static Event<MouseMovedEventArgs> MouseMovedEvent;
		static Event<MouseScrolledEventArgs> MouseScrolledEvent;

		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}

#endif //HEIRLOOM_INPUT_H
