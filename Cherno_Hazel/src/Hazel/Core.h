#pragma once

#ifdef VS_CODE_ONLY_DEFINE
// 仅为了在 VSCode 中查看时代码提示正常，运行会报错
	#define HZ_PLATFORM_WINDOWS
	#define HZ_BUILD_DLL
#endif

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif // HZ_BUILD_DLL
#else
	#error Hazel only supports WINDOWS!
#endif // HZ_PLATFORM_WINDOWS

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
	#define IMGUI_IMPL_OPENGL_DEBUG
#endif // HZ_DEBUG

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(Fn) std::bind(&Fn, this, std::placeholders::_1)