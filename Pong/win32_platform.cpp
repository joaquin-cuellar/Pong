#include <Windows.h>

static bool isRunning = true;

struct Buffer
{
	int height, width;
	void* memory;
	BITMAPINFO bitmapInfo;

	float scale = 100;
};
Buffer buffer;

#include "renderer.cpp"
#include "platformCommon.cpp"
#include "game.cpp"

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		isRunning = false;
		break;

	case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			buffer.width = rect.right - rect.left;
			buffer.height = rect.bottom - rect.top;

			int bufferSize = buffer.width * buffer.height * sizeof(unsigned int);

			if (buffer.memory) VirtualFree(buffer.memory, 0, MEM_RELEASE);
			buffer.memory = VirtualAlloc(0, bufferSize, 
				MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			buffer.bitmapInfo.bmiHeader.biSize = sizeof(buffer.bitmapInfo);
			buffer.bitmapInfo.bmiHeader.biWidth = buffer.width;
			buffer.bitmapInfo.bmiHeader.biHeight = buffer.height;
			buffer.bitmapInfo.bmiHeader.biPlanes = 1;
			buffer.bitmapInfo.bmiHeader.biBitCount = 32;
			buffer.bitmapInfo.bmiHeader.biCompression = BI_RGB;
		}
		break;


	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Create a Window Class
	WNDCLASS WindowClass = {};
	// Display Horizontally and Vertically
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	// Name to Display for Window Class
	WindowClass.lpszClassName = L"Game Window Class";
	// Callback function for when window is modified
	WindowClass.lpfnWndProc = WindowCallback;

	//Register Class
	RegisterClass(&WindowClass);

	//Create Window
	HWND window = CreateWindow(
		WindowClass.lpszClassName,
		L"Kiko Pong", //Window Display Name
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, //Window Display style
		CW_USEDEFAULT, //Windows preffered X
		CW_USEDEFAULT,//Windows preffered Y
		1280, //Width
		720, //Height
		0,
		0,
		hInstance,
		0
	);

	HDC hdc = GetDC(window);

	Input input = {};

	//Initialize
	InitializeGame();

	float deltaTime = 0.0166f; //seconds per frame (60 fps)
	LARGE_INTEGER frameStartTime;
	QueryPerformanceCounter(&frameStartTime);

	float performanceFrequency;
	{
		LARGE_INTEGER performance;
		QueryPerformanceFrequency(&performance);
		performanceFrequency = (float)performance.QuadPart;
	}

	//Loop Window
	while (isRunning)
	{

		//Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++)
		{
			input.button[i].hasChanged = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{

			switch (message.message)
			{
			case WM_KEYUP:
			case WM_KEYDOWN:
			{
				unsigned int vkCode = (unsigned int)message.wParam;
				bool isDown = ((message.lParam & (1 << 31)) == 0);

#define proccessButton(b, vk) case vk:\
input.button[b].hasChanged = isDown != input.button[b].isDown;\
input.button[b].isDown = isDown;\
break;\

				switch (vkCode)
				{
					proccessButton(BUTTON_UP, VK_UP)
					proccessButton(BUTTON_DOWN, VK_DOWN)
					proccessButton(BUTTON_ALTUP, VK_PRIOR)
					proccessButton(BUTTON_ALTDOWN, VK_NEXT)
					proccessButton(BUTTON_ENTER, VK_RETURN)
					proccessButton(BUTTON_ESCAPE, VK_ESCAPE)
				}
			}break;

			default:
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}

		//Simulate
		SimulateGame(&input, deltaTime);

		//Render
		StretchDIBits(hdc, 0, 0, buffer.width, buffer.height, 0, 0, buffer.width, buffer.height, buffer.memory,
			&buffer.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		
		LARGE_INTEGER frameEndTime;
		QueryPerformanceCounter(&frameEndTime);

		deltaTime = (float)(frameEndTime.QuadPart - frameStartTime.QuadPart) / performanceFrequency;

		frameStartTime = frameEndTime;
	}

	


}