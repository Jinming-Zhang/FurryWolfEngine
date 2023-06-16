#pragma once
#include "utils/Time/ITime.h"
namespace WolfTime {
	class Time
	{
	public:
		~Time();
		static float DeltaTime;

		static float CurrentTimestamp();
		static void SetTimer(ITime* t);
	private:
		static ITime* timer;
	};
}

