#pragma once

struct point {
	double x, y;
	point(double x, double y) { this->x = x; this->y = y; };
	bool operator < (const point& str) const
	{
		return (y < str.y);
	}
	bool operator > (const point& str) const
	{
		return (y > str.y);
	}
};
