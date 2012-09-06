#include "tools.h"

SDL_Rect	create_position(int x, int y, int w, int h)
{
	SDL_Rect	position;

	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
	return (position);
}

