#pragma once

#include "Hazel\Window.h"

namespace Hazel {

	class HAZEL_API WindowsWindow : public Window {
	public:
		void OnUpdate() override {

		}

		unsigned int GetWidth() override{
			return Width;
		}
	};

}