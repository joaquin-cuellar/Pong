#define button(b) input->button[b].isDown
#define buttonDown(b) input->button[b].isDown && input->button[b].hasChanged
#define buttonUp(b) !input->button[b].isDown && input->button[b].hasChanged

#include "resources.cpp"

Paddle paddle1;
Paddle paddle2;
Ball ball;
Object arena;

bool isMultiplayer = true;

static int player1Score = 0;
static int player2Score = 0;

static void ResetArena()
{
	arena.height = 80;
	arena.width = 160;
	arena.color = 0xfff;

	paddle1.x = (-arena.width / 2) + 5;
	paddle2.x = (arena.width /2) - 5;

	paddle1.y = paddle2.y = 0;

	paddle1.height = paddle2.height = arena.height / 3.5f;

	ball.x = ball.y = 0;

	ball.direction.x = ball.direction.y = 0;
	ball.maxSpeed = 800;
	ball.bounceMultiplier = 1.2f;
}

static void InitializeGame()
{
	player1Score = player2Score = 0;

	ResetArena();
}

inline void throwBall()
{
	ball.movementSpeed = 20;

	byte random = std::rand() % 2;
	ball.direction.x = random == 1 ? -1 : 1;
	random = std::rand() % 2;
	ball.direction.y = random == 1 ? -1 : 1;
}

inline void pointScored()
{
	ball.direction.x = ball.direction.y = 0;

	ResetArena();

	throwBall();
}

static void SimulateGame(Input* input, float deltaTime)
{
	//Quit Input
	if (button(BUTTON_ESCAPE)) isRunning = false;

	//Restart Game
	if (button(BUTTON_ENTER))
	{
		InitializeGame();
		throwBall();
	}

	//Paddle Input
	if (button(BUTTON_UP))
	{
		paddle1.move(1, deltaTime, arena.height / 2, -arena.height / 2);
	}
	else if (button(BUTTON_DOWN))
	{
		paddle1.move(-1, deltaTime, arena.height / 2, -arena.height / 2);
	}

	if (isMultiplayer)
	{
		if (button(BUTTON_ALTUP))
		{
			paddle2.move(1, deltaTime, arena.height / 2, -arena.height / 2);
		}
		else if (button(BUTTON_ALTDOWN))
		{
			paddle2.move(-1, deltaTime, arena.height / 2, -arena.height / 2);
		}
	}
	
	// BALL MOVEMENT
	ball.direction = normalize(ball.direction.x, ball.direction.y);

	ball.x += ball.movementSpeed * deltaTime * ball.direction.x;
	ball.y += ball.movementSpeed * deltaTime * ball.direction.y;

	// If ball touches paddle, bounce it
	if (ball.x + (ball.width / 2) >= paddle2.x - (paddle2.width / 2)
		&& ball.y - (ball.height / 2) <= paddle2.y + (paddle2.height / 2)
		&& ball.y + (ball.height / 2) >= paddle2.y - (paddle2.height / 2))
	{
		float yBounce = 1;//(ball.y - paddle2.y);

		ball.bounce(-1, yBounce);
	}
			

	if (ball.x - (ball.width / 2) <= paddle1.x + (paddle1.width / 2)
		&& ball.y - (ball.height / 2) <= paddle1.y + (paddle1.height / 2)
		&& ball.y + (ball.height / 2) >= paddle1.y - (paddle1.height / 2))
	{
		float yBounce = 1;//(ball.y - paddle1.y);

		ball.bounce(-1, yBounce);
	}
			

	// If ball touches arena top or bottom, bounce it
	if (ball.y + (ball.height / 2) >= arena.height / 2)
		ball.bounce(1, -1);
	if (ball.y - (ball.height / 2) <= -arena.height / 2)
		ball.bounce(1, -1);

	// If ball touches arena sides, then end game
	if (ball.x + (ball.width / 2) >= arena.width / 2)
	{
		player1Score++;
		pointScored();
	}
	if (ball.x - (ball.width / 2) <= -arena.width / 2)
	{
		player2Score++;
		pointScored();
	}

	//Render
	ClearScreen(0xFFC0CB);
	arena.Render();
	paddle1.Render();
	paddle2.Render();
	ball.Render();
}