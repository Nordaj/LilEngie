#include <ctime>
#include <chrono>
#include <ratio>
#include "Debug.h"
#include "Time.h"

namespace Time
{
	//Private
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
}

float Time::Get(Unit unit)
{
	using namespace std;
	using namespace chrono;

	switch (unit)
	{
		case Nanoseconds:
			return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
		case Microseconds:
			return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() * 0.001f;
		case Milliseconds:
			return duration_cast<microseconds>(high_resolution_clock::now() - start).count() * 0.001f;
		case Seconds:
			return duration_cast<milliseconds>(high_resolution_clock::now() - start).count() * 0.001f;
		case Minutes:
			return duration_cast<seconds>(high_resolution_clock::now() - start).count() * 0.016666f;
		default:
			ERROR("Invalid time unit.");
	}
}
