#pragma once

#include <chrono>

#include "common/types/SmartPointers.h"

#define NS_TO_MS 1e-6f
#define MS_TO_S 1e-3f

/*!
 * @brief TimePoint typedef
 * @details A typedef for a time point.
*/
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

/*!
 * @brief Timer class
 * @details A class that contains functions to get the time in milliseconds and nanoseconds.
*/
class Timer
{
protected:
	static const std::chrono::high_resolution_clock s_Clock;

	TimePoint m_StartTime;
	TimePoint m_EndTime;

public:
	Timer();
	Timer(Timer&) = delete;
	virtual ~Timer() = default;

	/*!
	 @brief Gets the current time.
	 @return TimePoint The current time.
	*/
	static TimePoint Now();

	float getTimeMs() const { return (float)(s_Clock.now() - m_StartTime).count() * NS_TO_MS; }
	float getTimeNs() const { return (s_Clock.now() - m_StartTime).count(); }
};
