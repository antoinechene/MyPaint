#ifndef __ID_controler_H__
#define __ID_controler_H__

#include <SDL/SDL.h>
#include <unistd.h>
#include <list>
#include "tools.h"
#include "colors.h"
#include "model.h"

class	controler
{
public:
	controler();
	~controler();
	void	init();
	Uint32	choose_color();
	void	add_button(button* but);
	void	check_tools(SDL_Surface* screen,model* mod, bool button, draw_zone*
	draw_zone, SDL_Surface* inter);
	int	event_button(SDL_Surface* screen, model*
	mod, draw_zone* draw, SDL_Surface* interface);
	int	check_button(SDL_Surface* screen, model*
	mod, draw_zone* draw_zone, SDL_Surface* interface);
	void	set_colors(model* mod, SDL_Surface* screen, SDL_Surface* inter);
	void	get_second_click(model* mod, draw_zone* draw);
	void	get_first_click(model* mod, draw_zone* draw);
	void	set_color_rightc(Uint32);
	void	set_color_leftc(Uint32);

private:
	int			focus;
	SDL_Event		event;
	SDL_Rect		work_pos;
	SDL_Surface*		work_zone;
	std::list<button*>*	buttons;
	Uint32			color_leftc;
	Uint32			color_rightc;
};

#endif
