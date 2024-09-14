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

#define BIT(x) (1 << x)