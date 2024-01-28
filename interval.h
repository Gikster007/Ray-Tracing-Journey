#pragma once

#include <limits>

const double i = std::numeric_limits<double>::infinity();

class Interval
{
public:
	double min, max;

	Interval() : min(+i), max(-i) {}
	Interval(double _min, double _max) : min(_min), max(_max) {}

	bool contains(double x) const { return min <= x && x <= max; }
	bool surrounds(double x) const { return min < x && x < max; }

	double clamp(double x) const 
	{
		if (x < min)
			return min;
		if (x > max)
			return max;
		return x;
	}

	static const Interval empty, universe;
};

const static Interval empty(+i, -i);
const static Interval universe(-i, +i);