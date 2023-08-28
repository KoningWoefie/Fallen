#ifndef TIMER_H 
#define TIMER_H 

#include <GLFW/glfw3.h>

//Copyright 2023 Sander Hoving (Fuck you Gideon)

class Timer
{ 
public: 
    Timer(); 
    virtual ~Timer();

	void StartTimer();
	void StopTimer();

	float Seconds();

	bool IsStarted() { return _started; }
private:
	double _sec();

	float _seconds;
	double startSec;

	bool _started;
}; 
#endif // timer_H 
