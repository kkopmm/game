#pragma once
#define _CRT_SECURE_NO_WARNINGS  1
#pragma once
#include <chrono>
class TimerClock;
class TimerClock
{
public:
	TimerClock() {
		update();
	}

	~TimerClock() {
	}

	void update() {
		_start = std::chrono::high_resolution_clock::now();
	}
	//获取秒
	double getSecond() {
		return getMicroSec() * 0.000001;
	}
	//获取毫秒
	double getMilliSec() {
		return getMicroSec() * 0.001;
	}
	//获取微妙
	long long getMicroSec() {
		//当前时钟减去开始时钟的count
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock>_start;
};