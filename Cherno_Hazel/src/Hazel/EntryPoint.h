#pragma once

#ifdef HZ_PLATFORM_WINDOWS
#include "spdlog\spdlog.h"

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv) {
	printf("Start Hazel App");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#else
	#error Hazel only supports WINDOWS!
#endif // HZ_PLATFORM_WINDOWS
