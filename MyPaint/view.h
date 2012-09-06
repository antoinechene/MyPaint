#ifndef view_h
#define view_h

#include <SDL/SDL.h>
#include <unistd.h>
#include "tools.h"
#include "draw_zone.h"
#include "controler.h"
	class view
	{
		public:
			view();
			~view();
			int	create_box();
			int	create_button_color(controler* control);
			int	init_window();
			int	create_button_tools(controler* control);
			int	create_interface(controler*
			control, int width, int height);
			SDL_Surface*	get_screen();
			int	button_menu(controler* control);
			draw_zone*	get_draw_zone();
			SDL_Surface*	get_interface();
			SDL_Rect*	get_pos_inter();
			void	init_color_used(controler* control);


		private:
			int		width;
			int		height;
			SDL_Surface*	screen;
			SDL_Surface*	interface;
			SDL_Rect	pos_inter;
			draw_zone*	draw;
	};

#endif
