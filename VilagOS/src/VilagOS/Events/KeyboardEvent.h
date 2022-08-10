#pragma once

#include "Event.h"

namespace VilagOS {
	class VOS_API KeyboardEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput) //This looks much nicer now with macros.

	protected: 
		int m_KeyCode;
		//constructor is protected because I dont wanan make any instances of 
		//this class it's not an actual event per se. Rather it's just a parent
		//class for actual events which are KeyPressed and KeyReleased.
		KeyboardEvent(int keycode): m_KeyCode(keycode) {}
	};

	class VOS_API KeyPressedEvent : public KeyboardEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyboardEvent(keycode), m_RepeatCount(repeatCount) {}

		//Engine without holding down a button option sucks ngl.
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToPrint() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent" << m_KeyCode << " (" << m_RepeatCount << " repeats).";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed) //This looks much nicer now with macros.

	private:
		int m_RepeatCount;
	};

	class  VOS_API KeyReleasedEvent: public KeyboardEvent{
	public:
		KeyReleasedEvent(int keycode) : KeyboardEvent(keycode) {}

		std::string ToPrint() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyReleased) 

	};

}