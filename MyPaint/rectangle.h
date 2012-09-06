#ifndef rectangle_h
#define rectangle_h
#include "shape.h"
#include <SDL/SDL.h>
#include <unistd.h>

class rectangle: public shape
{
	public:
		rectangle();
		~rectangle();
		void	init(SDL_Rect* rect);
		SDL_Rect*	get_rect();

	private:
		SDL_Rect	rect;

};


#endif
