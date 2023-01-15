struct ButtonState
{
	bool isDown;
	bool hasChanged;
};

enum
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_ALTUP,
	BUTTON_ALTDOWN,
	BUTTON_ENTER,
	BUTTON_ESCAPE,
	BUTTON_TAB,

	BUTTON_COUNT
};

struct Input
{
	ButtonState button[BUTTON_COUNT];
};