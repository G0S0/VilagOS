#pragma once

#include "Core.h"

#include <string>
#include <functional>

namespace VilagOS {
	enum class EventType { 
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender, 
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	//yknow maybe at some point I will not care exactly what event has 
	//happend but what caused it so im making an EventCategory as well.
	//
	enum EventCategory { //should i put enum class?
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

//just some macros to save myself some space
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType;}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	class VOS_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0; //To be removed from any other configuration except Debug since 
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToPrint() const { return GetName(); }	//by default return the name of the event 
																	//but is to be overwritten so that each event prints what it wants
																
		//checks if this Event is in the EventCategory passed as an argument
		inline bool IsInCategory(EventCategory category) { 
			return GetCategoryFlags() & category;	//if it returns 0 then it isn't in that category, if it returns anything else then it is,
													//however this doesnt tell us anything about other categories. Maybe il make so it returns
													//all the categories later.
		}
	protected: 
		bool m_Handled = false; //need this flag so that Events are handled only once. 
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event){}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator <<(std::ostream& os, const Event& e) {
		return os << e.ToPrint();
	}
}