#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" //This fixes the overloaded output operator for events issue 

namespace VilagOS {
	class VOS_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//Core log macros
#define VOS_CORE_ERROR(...)		:: VilagOS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VOS_CORE_WARN(...)		:: VilagOS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VOS_CORE_INFO(...)		:: VilagOS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VOS_CORE_TRACE(...)		:: VilagOS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VOS_CORE_FATAL(...)		:: VilagOS::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define VOS_CLIENT_ERROR(...)	:: VilagOS::Log::GetClientLogger()->error(__VA_ARGS__)
#define VOS_CLIENT_WARN(...)    :: VilagOS::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VOS_CLIENT_INFO(...)    :: VilagOS::Log::GetClientLogger()->info(__VA_ARGS__)
#define VOS_CLIENT_TRACE(...)   :: VilagOS::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VOS_CLIENT_FATAL(...)   :: VilagOS::Log::GetClientLogger()->fatal(__VA_ARGS__)