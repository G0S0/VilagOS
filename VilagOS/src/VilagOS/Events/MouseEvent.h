#pragma once

#include "Event.h"

namespace VilagOS {
	class VOS_API MouseMovedEvent : public Event{
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToPrint() const override{
			std::stringstream ss;
			ss << "MouseX: " << GetX() << " MouseY: " << GetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private: 
		int m_MouseX, m_MouseY;
	};

	class VOS_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y): m_offsetX(x), m_offsetY(y) {}

		inline float GetX() const { return m_offsetX; }
		inline float GetY() const { return m_offsetY; }

		std::string ToPrint() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent " << GetX() << " by x axis and for " << GetY() << " by y axis.";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled) //technically it is possible to scroll with button but im not sure how that works so il add it later.
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:
		int m_offsetX, m_offsetY;
	};

	class VOS_API MouseButtonEvent : public Event {
	public:
		inline int getButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryMouseButton)
	protected: //dont wanna create this event actually
		
		MouseButtonEvent(int button): m_button(button) {}

		int m_button;
	};

	class VOS_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToPrint() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent" << getButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class VOS_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToPrint() const override{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:" << getButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}