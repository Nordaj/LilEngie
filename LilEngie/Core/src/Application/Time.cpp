#include <ctime>
#include <chrono>
#include <ratio>
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

	if (unit == Unit::Nanoseconds)
		return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
	else if (unit == Unit::Microseconds)
		return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() * 0.001f;
	else if (unit == Unit::Milliseconds)
		return duration_cast<microseconds>(high_resolution_clock::now() - start).count() * 0.001f;
	else if (unit == Unit::Seconds)
		return duration_cast<milliseconds>(high_resolution_clock::now() - start).count() * 0.001f;
	else if (unit == Unit::Minutes)
		return duration_cast<seconds>(high_resolution_clock::now() - start).count() * 0.016666f;
}
