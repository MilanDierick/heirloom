// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_CORE_H
#define HEIRLOOM_CORE_H

#include <memory>

// https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
#ifdef _WIN32
#ifdef _WIN64
#define HL_PLATFORM_WINDOWS
#else
		#define HL_PLATFORM_WINDOWS
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
		#define HL_PLATFORM_IOS
		#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
		#define HL_PLATFORM_MACOS
		#error "MacOS is not supported!"
#else
		#error "Unknown Apple platform!"
#endif
#elif defined(__ANDROID__)
#define HL_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
#define HL_PLATFORM_LINUX
#else
#error "Unknown platform!"
#endif

#ifdef HL_DEBUG
#if defined(HL_PLATFORM_WINDOWS)
#define HL_DEBUGBREAK() __debugbreak()
#elif defined(HL_PLATFORM_LINUX)
#include <csignal>
#define HL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define HL_ENABLE_ASSERTS
#else
#define HL_DEBUGBREAK()
#endif

#include "Log.h"

#include "Heirloom/Profiler/Instrumentation.h"

#ifdef HL_ENABLE_ASSERTS // false -> break
#define HL_ASSERT(x, ...) { if(!(x)) { HL_ERROR("Assertion Failed: {0}", __VA_ARGS__); HL_DEBUGBREAK(); } }
#define HL_CORE_ASSERT(x, ...) { if(!(x)) { HL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HL_DEBUGBREAK(); } }
#else
#define HL_ASSERT(x, ...)
	#define HL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define ALIGNED(x) __attribute__((aligned(x))) // NOLINT

namespace Heirloom
{
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using WeakRef = std::weak_ptr<T>;
}

#endif //HEIRLOOM_CORE_H
