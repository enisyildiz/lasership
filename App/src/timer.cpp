#include "timer.h"

Timer::Timer(int duration, bool repeat, bool autostart, std::function<void()> cb)
{
	this->timerTime = duration;
	this->isActive = false;
	this->repeat = repeat;
	this->callback = cb;

	if (autostart == true)
	{
		Timer::activate();
	}
}

void Timer::activate()
{
	this->isActive = true;
	this->startTime = std::chrono::steady_clock::now();
}

void Timer::deactivate()
{
	this->isActive = false;

	if (this->repeat == true)
	{
		Timer::activate();
	}
}

void Timer::update()
{
	int timeInMiliSecond = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->startTime).count();
	
	if (this->isActive == true)
	{
		if (timeInMiliSecond >= (this->timerTime))
		{
			Timer::deactivate();
			this->callback();
		}
	}
}