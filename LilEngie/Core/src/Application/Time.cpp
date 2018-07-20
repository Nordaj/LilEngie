#include <ctime>
#include <chrono>
#include <ratio>
#include "Debug.h"
#include "Time.h"

namespace Time
{
	//Im lazy
	typedef std::chrono::high_resolution_clock::time_point tPoint;
	typedef std::chrono::high_resolution_clock clock;

	//Public
	float deltaTime = 0;

	//Private
	tPoint start = clock::now();
	tPoint strtFrame = clock::now();
}

float Time::Get(Unit unit)
{
	using namespace std::chrono;

	switch (unit)
	{
		case Nanoseconds:
			return duration_cast<nanoseconds>(clock::now() - start).count();
		case Microseconds:
			return duration_cast<nanoseconds>(clock::now() - start).count() * 0.001f;
		case Milliseconds:
			return duration_cast<microseconds>(clock::now() - start).count() * 0.001f;
		case Seconds:
			return duration_cast<milliseconds>(clock::now() - start).count() * 0.001f;
		case Minutes:
			return duration_cast<seconds>(clock::now() - start).count() * 0.016666f;
		default:
			ERROR("Invalid time unit.");
	}
}

void Time::StartFrame()
{
	strtFrame = clock::now();
}

void Time::EndFrame()
{
	using namespace std::chrono;
	deltaTime = duration_cast<milliseconds>(clock::now() - strtFrame).count() * 0.001f;
}
