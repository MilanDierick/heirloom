// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_KEYEVENTARGS_H
#define HEIRLOOM_KEYEVENTARGS_H

#include "Event.h"

namespace Heirloom
{
	struct KeyEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyEventArgs(const KeyCode keyCode)
				: key_code(keyCode)
		{
		}

		KeyCode key_code;
	};

	struct KeyPressedEventArgs : EventArgs
	{
		[[nodiscard]] KeyPressedEventArgs(const KeyCode keyCode, const int repeatCount)
				: key_code(keyCode),
                  RepeatCount(repeatCount)
		{
		}

		KeyCode key_code;
		int RepeatCount;
	};

	struct KeyReleasedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyReleasedEventArgs(const KeyCode keyCode)
				: key_code(keyCode)
		{
		}

		KeyCode key_code;
	};

	struct KeyTypedEventArgs : EventArgs
	{
		[[nodiscard]] explicit KeyTypedEventArgs(const KeyCode keyCode)
				: key_code(keyCode)
		{
		}

		KeyCode key_code;
	};
}


#endif //HEIRLOOM_KEYEVENTARGS_H
