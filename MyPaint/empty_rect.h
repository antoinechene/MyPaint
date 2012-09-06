#ifndef __EMPTY_RECT_H__
#define __EMPTY_RECT_H__

#include <SDL/SDL.h>
#include <unistd.h>
#include "tools.h"
#include "colors.h"
#include "model.h"
#include "shape.h"


class empty_rect: public shape
{
	public:
		empty_rect();
		~empty_rect();
		void	set_empty_rect(size_t x, size_t y, size_t w, size_t h, SDL_Rect* side);
		SDL_Rect*	get_side1();
		SDL_Rect*	get_side2();
		SDL_Rect*	get_side3();
		SDL_Rect*	get_side4();

	private:
		SDL_Rect	side1;
		SDL_Rect	side2;
		SDL_Rect	side3;
		SDL_Rect	side4;
};

#endif
