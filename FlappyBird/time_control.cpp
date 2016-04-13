#include "time_control.h"

TimeControl::TimeControl(const std::vector<clock_t>& i) 
	: interval(i), ite(interval.cbegin()), targetTime(clock() + *ite)
{
}

TimeControl::TimeControl(std::vector<clock_t>&& i) 
	: interval(std::move(i)), ite(interval.cbegin()), targetTime(clock() + *ite)
{ 
}

bool TimeControl::TimeTargetComplete()
{
	if (clock() >= targetTime)
	{
		ite++;
		targetTime = (ControlEnd() ? LONG_MAX : clock() + *ite);
		return true;
	}
	return false;
}

bool TimeControl::ControlEnd()
{
	return ite == interval.cend();
}

void TimeControl::SetEnd()
{
	ite = interval.cend();
	targetTime = LONG_MAX;
}

void TimeControl::Reset()
{ 
	ite = interval.cbegin();
	targetTime = clock() + *ite;
}

void TimeControl::ResetToLastInterval()
{ 
	ite--;
	targetTime = clock() + *ite;
}