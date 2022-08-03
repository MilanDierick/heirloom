//
// Created by developer on 09/12/2021.
//

#ifndef HEIRLOOM_MOUSECODES_H
#define HEIRLOOM_MOUSECODES_H

#include <ostream>

namespace Heirloom
{
	using MouseCode = enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define HL_MOUSE_BUTTON_0      ::Heirloom::Mouse::Button0
#define HL_MOUSE_BUTTON_1      ::Heirloom::Mouse::Button1
#define HL_MOUSE_BUTTON_2      ::Heirloom::Mouse::Button2
#define HL_MOUSE_BUTTON_3      ::Heirloom::Mouse::Button3
#define HL_MOUSE_BUTTON_4      ::Heirloom::Mouse::Button4
#define HL_MOUSE_BUTTON_5      ::Heirloom::Mouse::Button5
#define HL_MOUSE_BUTTON_6      ::Heirloom::Mouse::Button6
#define HL_MOUSE_BUTTON_7      ::Heirloom::Mouse::Button7
#define HL_MOUSE_BUTTON_LAST   ::Heirloom::Mouse::ButtonLast
#define HL_MOUSE_BUTTON_LEFT   ::Heirloom::Mouse::ButtonLeft
#define HL_MOUSE_BUTTON_RIGHT  ::Heirloom::Mouse::ButtonRight
#define HL_MOUSE_BUTTON_MIDDLE ::Heirloom::Mouse::ButtonMiddle


#endif //HEIRLOOM_MOUSECODES_H
