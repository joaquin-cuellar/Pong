#define button(b) input->button[b].isDown
#define buttonDown(b) input->button[b].isDown && input->button[b].hasChanged
#define buttonUp(b) !input->button[b].isDown && input->button[b].hasChanged


struct Frog
{
	float x, y;
	unsigned int color;
	float size;
	float speed;
	float baseSpeed;
};
Frog frog;

static void InitializeGame()
{
	frog.color = 0x00FF00;
	frog.size = 10;
	frog.x = 0;
	frog.y = 0;
	frog.baseSpeed = 20;
}

static void SimulateGame(Input* input, float deltaTime)
{
	ClearScreen(0xFFC0CB);

	if (button(BUTTON_SHIFT))
		frog.speed = frog.baseSpeed * 3.5f;
	else
		frog.speed = frog.baseSpeed;

	if (button(BUTTON_UP))
		frog.y += frog.speed * deltaTime;
	if (button(BUTTON_DOWN))
		frog.y -= frog.speed * deltaTime;
	if (button(BUTTON_LEFT))
		frog.x -= frog.speed * deltaTime;
	if (button(BUTTON_RIGHT))
		frog.x += frog.speed * deltaTime;

	DrawRect(frog.size, frog.size, frog.x, frog.y, frog.color);
}
