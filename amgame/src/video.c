#include <game.h>

#define SIDE 30
static int w, h;

static void init()
{
	AM_GPU_CONFIG_T info = {0};
	ioe_read(AM_GPU_CONFIG, &info);
	w = info.width;
	h = info.height;
}

static void draw_tile(int x, int y, int w, int h, uint32_t color)
{
	uint32_t pixels[w * h]; // WARNING: large stack-allocated memory
	AM_GPU_FBDRAW_T event = {
		.x = x,
		.y = y,
		.w = w,
		.h = h,
		.sync = 1,
		.pixels = pixels,
	};
	for (int i = 0; i < w * h; i++)
	{
		if (i < (w * h) / 2)
		{
			pixels[i] = color;
		}
		else
		{
			pixels[i] = 0x321688;
		}
	}
	ioe_write(AM_GPU_FBDRAW, &event);
}

void splash()
{
	init();
	for (int x = 0; x * SIDE <= w; x++)
	{
		for (int y = 0; y * SIDE <= h; y++)
		{
			if ((x & 1) ^ (y & 1))
			{
				draw_tile(x * SIDE, y * SIDE, SIDE - 5, SIDE + 5, 0xffffff); // white
			}
		}
	}
}
