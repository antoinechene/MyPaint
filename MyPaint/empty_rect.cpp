#include <SDL/SDL.h>
#include "draw_zone.h"
#include "empty_rect.h"

empty_rect::empty_rect()
{
}

empty_rect::~empty_rect()
{
}


void	empty_rect::set_empty_rect(size_t x, size_t y, size_t w, size_t h, SDL_Rect* side)
{
	
	side->x = x;
	side->y = y;
	side->h = h;
	side->w = w;
}

SDL_Rect*	empty_rect::get_side1()
{
	return (&(this->side1));
}

SDL_Rect*	empty_rect::get_side2()
{
	return (&(this->side2));
}

SDL_Rect*	empty_rect::get_side3()
{
	return (&(this->side3));
}

SDL_Rect*	empty_rect::get_side4()
{
	return (&(this->side4));
}
