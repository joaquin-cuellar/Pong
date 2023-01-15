#include <cmath>

inline int clamp(int value, int minimum, int maximum)
{
	if (value < minimum) return minimum;
	else if (value > maximum) return maximum;
	else return value;
}

struct Vector2
{
	float x, y = 0;

	Vector2()
	{
		x = y = 0;
	}

	Vector2(float xIn, float yIn)
	{
		x = xIn;
		y = yIn;
	}

};

inline Vector2 normalize(double x, double y)
{
	double length = std::sqrt(x * x + y * y);

	if (length == 0) return Vector2(0, 0);

	x /= length;
	y /= length;

	return Vector2(x, y);
}