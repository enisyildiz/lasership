#include <chrono>
#include <functional>

class Timer{
public:
	int timerTime;
	std::chrono::steady_clock::time_point startTime;
	bool isActive = false;
	bool repeat = repeat;
	std::function<void()> callback;

	Timer(int duration, bool repeat, bool autostart, std::function<void()> cb);

	void activate();
	void deactivate();
	void update();
};