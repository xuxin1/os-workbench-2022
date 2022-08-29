#include <game.h>

#define KEYNAME(key) \
	[AM_KEY_##key] = #key,
static const char *key_names[] = {
	AM_KEYS(KEYNAME)};
static int init_x = 0, init_y = 0;

void show_box(int x, int y)
{

	uint32_t pixel[16 * 16];
	AM_GPU_FBDRAW_T event = {
		.x = x,
		.y = y,
		.w = 16,
		.h = 16,
		.sync = 1,
		.pixels = pixel,
	};
	for (int i = 0; i < 16 * 16; i++)
	{
		pixel[i] = 0x3378C6;
	};
	ioe_write(AM_GPU_FBDRAW, &event);
}

void print_key()
{
	AM_INPUT_KEYBRD_T event = {.keycode = AM_KEY_NONE};
	ioe_read(AM_INPUT_KEYBRD, &event);
	if (event.keycode != AM_KEY_NONE && event.keydown)
	{
		puts("Key pressed: ");
		puts(key_names[event.keycode]);
		puts("\n");
	}
	if (event.keycode == AM_KEY_W && event.keydown)
	{
		show_box(init_x, init_y - 16);

		init_y = init_y - 16;
	}
	if (event.keycode == AM_KEY_A && event.keydown)
	{
		show_box(init_x - 16, init_y);
		init_x = init_x - 16;
	}
	if (event.keycode == AM_KEY_S && event.keydown)
	{
		show_box(init_x, init_y + 16);
		init_y = init_y + 16;
	}
	if (event.keycode == AM_KEY_D && event.keydown)
	{
		show_box(init_x + 16, init_y);
		init_x = init_x + 16;
	}
}
