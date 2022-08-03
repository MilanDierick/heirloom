#include "hlpch.h"
#include <GLFW/glfw3.h>
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Input.h"

namespace Heirloom
{
	Event<KeyPressedEventArgs> Input::KeyPressedEvent                   = Event<KeyPressedEventArgs>();
	Event<KeyReleasedEventArgs> Input::KeyReleasedEvent                 = Event<KeyReleasedEventArgs>();
	Event<KeyTypedEventArgs> Input::KeyTypedEvent                       = Event<KeyTypedEventArgs>();
	Event<MouseButtonPressedEventArgs> Input::MouseButtonPressedEvent   = Event<MouseButtonPressedEventArgs>();
	Event<MouseButtonReleasedEventArgs> Input::MouseButtonReleasedEvent = Event<MouseButtonReleasedEventArgs>();
	Event<MouseMovedEventArgs> Input::MouseMovedEvent                   = Event<MouseMovedEventArgs>();
	Event<MouseScrolledEventArgs> Input::MouseScrolledEvent             = Event<MouseScrolledEventArgs>();

	bool Input::IsKeyPressed(const KeyCode key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetKey(window, static_cast<int>(key));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const int state    = glfwGetMouseButton(window, static_cast<int>(button));

		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();

		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();

		return y;
	}
}
