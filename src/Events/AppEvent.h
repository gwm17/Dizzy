#pragma once

#include "Event.h"

namespace Dizzy {
	// Window closing is pure event (no data)
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {};

		EVENT_CATEGORY_SETUP(EventCategoryApp)
		EVENT_TYPE_SETUP(WindowClosed)
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int x, int y) :
			m_xSize(x), m_ySize(y)
		{
		}

		int GetXSize() { return m_xSize; }
		int GetYSize() { return m_ySize; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << " to size: (" << m_xSize << ", " << m_ySize << ")";
			return ss.str();
		}

		EVENT_CATEGORY_SETUP(EventCategoryApp)
		EVENT_TYPE_SETUP(WindowResized)

	private:
		int m_xSize, m_ySize;
	};

	class AppUpdatedEvent : public Event
	{
	public:
		AppUpdatedEvent() = default;

		EVENT_CATEGORY_SETUP(EventCategoryApp)
		EVENT_TYPE_SETUP(AppUpdated)
	};
}