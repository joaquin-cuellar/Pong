struct ButtonState
{
	bool isDown;
	bool hasChanged;
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_SHIFT,

	BUTTON_COUNT
};

struct Input
{
	ButtonState button[BUTTON_COUNT];
};