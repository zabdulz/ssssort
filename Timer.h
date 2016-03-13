#pragma once

#include <chrono>

/// A flexible timer. TimeT is the precision of the timing, while scalingFactor
/// is the factor by which the output will be scaled. The default is to print
/// return milliseconds with microsecond precision.
template<typename TimeT = std::chrono::microseconds, int scalingFactor = 1000, typename return_type = double>
struct TimerT {
	TimerT() {
		reset();
	}

	void reset() {
		start = std::chrono::system_clock::now();
	}

        return_type get() const {
		TimeT duration = std::chrono::duration_cast<TimeT>(std::chrono::system_clock::now() - start);
		return (duration.count() * 1.0) / scalingFactor;
	}

        return_type get_and_reset() {
		auto t = get();
		reset();
		return t;
	}

private:
	std::chrono::system_clock::time_point start;
};

/// A timer that is accurate to microseconds, formatted as milliseconds
typedef TimerT<std::chrono::microseconds, 1000, double> Timer;
