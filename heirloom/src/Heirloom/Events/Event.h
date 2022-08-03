// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_EVENT_H
#define HEIRLOOM_EVENT_H

#include <array>
#include <functional>
#include "Heirloom/Core/Core.h"

#define HL_MAX_EVENT_LISTENERS 32

namespace Heirloom
{
	struct EventArgs
	{
	};

	template <typename EventArgsType = EventArgs, typename EventCallbackFunc = std::function<void(EventArgsType)>>
	class Event
	{
	public:
		Event<EventArgsType, EventCallbackFunc>& operator+=(EventCallbackFunc eventCallbackFunc);

		void Invoke(EventArgsType eventArgs);

	private:
		std::array<EventCallbackFunc, HL_MAX_EVENT_LISTENERS> m_EventListeners = {};
		size_t m_EventListenerCount                                            = 0;
	};

	template <typename EventArgsType, typename EventCallbackFunc>
	Event<EventArgsType, EventCallbackFunc>& Event<EventArgsType, EventCallbackFunc>::operator+=(
			EventCallbackFunc eventCallbackFunc)
	{
		HL_CORE_ASSERT(m_EventListenerCount + 1 < HL_MAX_EVENT_LISTENERS,
				"Failed registering an event listener, only {0} listeners per event are supported!",
				HL_MAX_EVENT_LISTENERS);

		m_EventListeners[m_EventListenerCount] = eventCallbackFunc;
		++m_EventListenerCount;

		return *this;
	}

	template <typename EventArgsType, typename EventCallbackFunc>
	void Event<EventArgsType, EventCallbackFunc>::Invoke(EventArgsType eventArgs)
	{
		for (size_t index = 0; index < m_EventListenerCount; ++index)
		{
			m_EventListeners[index](eventArgs);
		}
	}
}

#endif //HEIRLOOM_EVENT_H
