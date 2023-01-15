class Object
{
public:
	float x, y;
	unsigned int color;
	float width, height;

public:Object()
	{
		x = y = 0;
		width = height = 0;
		color = 0;
	}

public : void Render()
	{
		DrawRect(width, height, x, y, color);
	}
};

class Paddle : public Object
{
public:
	float movementSpeed;

	Paddle():Object()
	{
		width = 2.5f;
		height = 25;
		movementSpeed = 35;
	}

public: void move(float moveMultiplier, float deltaTime, float upperLimits, float lowerLimits)
{
	float change;
	if (moveMultiplier > 0 && (y + (height / 2) >= upperLimits))
		change = 0;
	else if (moveMultiplier < 0 && (y - (height / 2) <= lowerLimits))
		change = 0;
	else
		change = movementSpeed * deltaTime * moveMultiplier;
	
	y += change;
}

};

class Ball : public Object
{
public:
	float movementSpeed;
	float maxSpeed;
	Vector2 direction;
	float bounceMultiplier;

	Ball() :Object()
	{
		direction.x = 0;
		direction.y = 0;
		width = 5;
		height = 5;
		movementSpeed = 20;
		maxSpeed = 80;
		bounceMultiplier = 1.2f;
	}

public: void bounce(float x = -1, float y = -1)
{
	direction.x *= x;
	direction.y *= y;

	if (movementSpeed < maxSpeed)
	{
		movementSpeed *= bounceMultiplier;
		if (movementSpeed > maxSpeed) movementSpeed = maxSpeed;
	}
}

};