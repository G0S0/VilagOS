#pragma once
#include <sstream>
#include <utility>
#include "Event.h"

namespace VilagOS {
	class VOS_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height): m_width(width), m_height(height){}

		std::pair<unsigned int, unsigned int> getSizes() const { //if this works well il implement getters this way in MouseEvents as well.
			std::pair sizes = std::make_pair(m_width, m_height);
			return sizes;
		}

		std::string ToPrint() const override {
			std::stringstream ss;
			ss << "WindowResizedEvent: (" << getSizes().first << ", "<< getSizes().second<<")";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowResize)

	private:
		unsigned int m_width, m_height;
	};

	class VOS_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)
	};


	//I was going to implement App events just as all the other events but Ive found a better way so il consider that one for now 
	//class VOS_API AppTickEvent : public Event { 
	//public:
	//	AppTickEvent() {}
	//	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	//	EVENT_CLASS_TYPE(AppTick)
	//};
	//
	//class VOS_API AppUpdateEvent : public Event {
	//public:
	//	AppUpdateEvent() {}
	//	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	//	EVENT_CLASS_TYPE(AppUpdate)
	//};
	//
	//class VOS_API AppRenderEvent : public Event {
	//public:
	//	AppRenderEvent() {}
	//	EVENT_CLASS_CATEGORY(EventCategoryApplication)
	//	EVENT_CLASS_TYPE(AppRender)
	//};
}