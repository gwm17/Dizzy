#pragma once

#include "Core/DZCore.h"

namespace Dizzy {

	enum class EventType
	{
		None=0,
		WindowClosed, WindowResized, WindowFocused, WindowLostFocused, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
		AppUpdated
	};

	enum EventCategory
	{
		EventCategoryNone = 0,
		EventCategoryWindow = BIT(0),
		EventCategoryKey = BIT(1),
		EventCategoryMouse = BIT(2),
		EventCategoryApp = BIT(3),
		EventCategoryInput = BIT(4)
	};

	//Some function generation automation to reduce code written for all events
	#define EVENT_CATEGORY_SETUP(cat) virtual int GetCategoryFlags() const override { return cat; }

	#define EVENT_TYPE_SETUP(type) static EventType GetStaticType() { return EventType::type; } \
								   virtual EventType GetEventType() const override { return GetStaticType(); } \
								   virtual const char* GetName() const override { return #type; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsCategory(EventCategory category) const { return GetCategoryFlags() & category; }
		bool m_isHandled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) :
			m_event(e)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& function)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.m_isHandled = function(static_cast<T&>(m_event));
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}