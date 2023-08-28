#include <src/timer.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

Timer::Timer() 
{ 
	_seconds = 0;
	startSec = 0;
	_started = false;
} 
Timer::~Timer() 
{ 
}

void Timer::StartTimer()
{
	startSec = _sec();
	_started = true;
}

void Timer::StopTimer()
{
	_seconds = 0;
	startSec = 0;
	_started = false;
}

float Timer::Seconds()
{
	if(!_started)
	{
		return 0.0f;
	}
	_seconds = _sec() - startSec;
	return _seconds;
}

double Timer::_sec()
{
	return glfwGetTime();
}
