#pragma once
namespace WolfTime {
	class ITime
	{
	public:
		virtual float CurrentTimestamp() = 0;
		virtual ~ITime() {};
	};
}
