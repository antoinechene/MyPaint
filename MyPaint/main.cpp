#include <iostream>
#include <SDL/SDL.h>
#include "draw_zone.h"
#include "button.h"
#include "tools.h"
#include "controler.h"
#include "paint.h"
#include "view.h"
#include "model.h"

int	main()
{
	paint		pain;
	SDL_Surface*	draws;

	pain.get_view()->create_interface(pain.get_controler(),
	1000, 800);
	pain.get_controler()->event_button(pain.get_view()->get_screen(), pain.get_model(),
	pain.get_view()->get_draw_zone(),pain.get_view()->get_interface());
	while (pain.get_model()->get_resize())
	{
		pain.get_model()->set_resize(false);
		draws = pain.get_view()->get_draw_zone()->get_work();

		draws = SDL_CreateRGBSurface(SDL_HWSURFACE,pain.get_view()->get_draw_zone()->get_work()->clip_rect.w,
				    pain.get_view()->get_draw_zone()->get_work()->clip_rect.h, 32, 0, 0, 0, 0);
		SDL_BlitSurface(pain.get_view()->get_draw_zone()->get_work(), NULL, draws, NULL);
		pain.get_view()->create_interface(pain.get_controler(), pain.get_model()->get_resize_x(), pain.get_model()->get_resize_y());
		pain.get_view()->get_draw_zone()->set_work(draws);
		pain.get_controler()->event_button(pain.get_view()->get_screen(), pain.get_model(),
		pain.get_view()->get_draw_zone(),pain.get_view()->get_interface());
	}
	return (0);
}
