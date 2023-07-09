#pragma once
#include "utils/Time/ITime.h"
namespace WolfTime {
	class FloatTimerBase :public ITime
	{
	public:
		virtual float CurrentTimestamp() override = 0;
	};
}

