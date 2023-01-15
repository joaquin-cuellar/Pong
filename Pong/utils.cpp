inline int clamp(int value, int minimum, int maximum)
{
	if (value < minimum) return minimum;
	else if (value > maximum) return maximum;
	else return value;
}