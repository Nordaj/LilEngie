#pragma once

namespace Time
{
	//Public
	extern float deltaTime; //Time elapsed from start of frame to end (in ms)

	enum Unit { Nanoseconds, Microseconds, Milliseconds, Seconds, Minutes };

	float Get(Unit unit = Milliseconds);
	void StartFrame();
	void EndFrame();
}

//Maybe change to TUnit if needed
typedef Time::Unit Unit;
