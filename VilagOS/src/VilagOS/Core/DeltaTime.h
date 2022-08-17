#pragma once

namespace VilagOS {
	class DeltaTime {
	public:
		DeltaTime(float time) : m_Time(time) {}

		float GetSeconds() const { return m_Time; }
		float GetMiliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time = 0.0f;
	};


}