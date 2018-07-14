#pragma once

namespace Time
{
	enum Unit { Nanoseconds, Microseconds, Milliseconds, Seconds, Minutes };

	float Get(Unit unit = Milliseconds);
}

//Maybe change to TUnit if needed
typedef Time::Unit Unit;
