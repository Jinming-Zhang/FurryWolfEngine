#pragma once
#include "GLFW/glfw3.h"
#include "utils/Time/FloatTimerBase.h"
namespace WolfTime {
	class GlfwTimer :public FloatTimerBase
	{
	public:
		GlfwTimer();
		virtual ~GlfwTimer()override;

		virtual float CurrentTimestamp() override;
	};
}

