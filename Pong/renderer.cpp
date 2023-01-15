#include "utils.cpp"

static void ClearScreen(unsigned int color = 0x000000)
{
	unsigned int* pixel = (unsigned int*)buffer.memory;
	for (int y = 0; y < buffer.height; y++)
		for (int x = 0; x < buffer.width; x++)
		{
			*pixel++ = color;//x ^ y;
		}
}

static void DrawRectByPixel(int width, int height, int xStart, int yStart, unsigned int color = 0x000000)
{
	int yEnd, xEnd;
	yEnd = yStart + height;
	xEnd = xStart + width;

	xStart = clamp(xStart, 0, buffer.width);
	yStart = clamp(yStart, 0, buffer.height);
	xEnd = clamp(xEnd, 0, buffer.width);
	yEnd = clamp(yEnd, 0, buffer.height);

	for (int y = yStart; y < yEnd; y++)
	{
		unsigned int* pixel = (unsigned int*)buffer.memory + xStart + y*buffer.width;

		for (int x = xStart; x < xEnd; x++)
		{
			*pixel++ = color;//x ^ y;
		}
	}
}

static void DrawRect(float width, float height, float x = 0, float y = 0, unsigned int color = 0x000000)
{
	int pixelX, pixelY, pixelWidth, pixelHeight;

	width /= buffer.scale;
	height /= buffer.scale;

	x /= buffer.scale;
	y /= buffer.scale;

	pixelWidth = width * buffer.height;
	pixelHeight = height * buffer.height;
	pixelX = x * buffer.height;
	pixelY = y * buffer.height;

	pixelX += buffer.width / 2;
	pixelY += buffer.height / 2;

	pixelX -= pixelWidth / 2;
	pixelY -= pixelHeight / 2;

	DrawRectByPixel(pixelWidth, pixelHeight, pixelX, pixelY, color);
}