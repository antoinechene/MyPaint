#include <iostream>
#include <SDL/SDL.h>
#include "draw_zone.h"
#include "button.h"

#include "controler.h"


controler::controler()
{
}

void	controler::init()
{
	this->buttons = new std::list<button*>();
	this->focus = -1;
}

void	controler::set_color_rightc(Uint32 col)
{
	this->color_rightc = col;
}

void	controler::set_color_leftc(Uint32 col)
{
	this->color_leftc = col;
}

controler::~controler()
{
	delete work_zone;
}

void	controler::add_button(button* but)
{
	this->buttons->push_back(but);
}

void	controler::set_colors(model* mod, SDL_Surface* screen, SDL_Surface* inter)
{
	SDL_Rect	pos;

	if (this->event.button.button == SDL_BUTTON_LEFT)
	{
		pos = create_position(45, screen->h - 90, 30, 30);
		this->color_leftc =  mod->get_pixel(this->event.button.x,
		this->event.button.y, screen);
		SDL_FillRect(inter, &pos,  mod->get_pixel(this->event.button.x,
		this->event.button.y, inter));
	}
	else if (this->event.button.button == SDL_BUTTON_RIGHT)
	{
		pos = create_position(45, screen->h - 50, 30, 30);
		this->color_rightc = mod->get_pixel(this->event.button.x,
		this->event.button.y, screen);
		SDL_FillRect(inter, &pos, mod->get_pixel(this->event.button.x,
		this->event.button.y, inter));

	}
}


int	controler::check_button(SDL_Surface* screen, model* mod, draw_zone* draw, SDL_Surface* inter)
{
	std::list<button*>::iterator	it;
	bool	button;

	it = this->buttons->begin();
	button = false;
	while (it != this->buttons->end())
	{
		if (this->event.button.y >= (*it)->get_pos()->y && this->event.button.y <= (*it)->get_pos()->y + 33
		&& this->event.button.x >= (*it)->get_pos()->x && this->event.button.x <= (*it)->get_pos()->x + 33)
		{
			this->focus = (*it)->get_type();
			button = true;

			break;
		}
		it ++;
	}
	this->check_tools(screen, mod, button, draw, inter);

	SDL_Flip(screen);
	return 0;
}

Uint32	controler::choose_color()
{
	if (this->event.button.button == SDL_BUTTON_LEFT)
		return (this->color_leftc);
	else
		return (this->color_rightc);
}

void	controler::check_tools(SDL_Surface* screen, model* mod, bool button, draw_zone* draw, SDL_Surface* inter)
{

	Uint32	col;

	if (this->focus == 0 && button == true)
		this->set_colors(mod, screen, inter);
	if (this->focus == 1 || this->focus == 2 || this->focus == 7 || this->focus == 8)
	{
		if (button == true)
		{
			this->get_first_click(mod, draw);
			this->get_second_click(mod, draw);
		}
		else
		{
			mod->set_click1_x(this->event.button.x - 100);
			mod->set_click1_y(this->event.button.y - 35);
			this->get_second_click(mod, draw);
		
		}
		col = choose_color();
		if (this->focus == 1)
			mod->draw_full_rect(draw, col);
		else if (this->focus == 2)
			mod->draw_empty_rect(draw, col);
		else if (this->focus == 7)
			mod->draw_circle(col, draw);
		else if (this->focus == 8)
			mod->draw_disc(col, draw);
		mod->add_surface(draw->get_work());

	}
	else if (this->focus == 3 || this->focus == 4 || this->focus == 13)
	{
		mod->new_window(draw, screen, this->focus);
		mod->add_surface(draw->get_work());
	}
	else if (this->focus == 5 && button == false)
	{
		this->color_leftc =  mod->get_pixel(this->event.button.x,
		this->event.button.y, screen);
		mod->add_surface(draw->get_work());
	}
	else if (this->focus == 6)
	{
		if (button == true)
			this->get_first_click(mod, draw);
		col = choose_color();
		mod->flood_fill(this->event.button.x - 100, this->event.button.y - 35,
		col, draw);
		mod->add_surface(draw->get_work());

	}
	else if (this->focus == 9)
	{
		col = choose_color();
		if (button == true)
			this->get_first_click(mod, draw);
		while (this->event.type != SDL_MOUSEBUTTONUP)
		{
			SDL_WaitEvent(&(this->event));
			mod->set_click1_x(this->event.button.x - 100);
			mod->set_click1_y(this->event.button.y - 35);
			col = choose_color();
			mod->circular_brush(col, draw, screen);
		}
		mod->add_surface(draw->get_work());

	}
	else if (this->focus == 10)
	{
		mod->zoom(draw, draw->get_work()->w * 0.9 , draw->get_work()->h * 0.9);
		mod->add_surface(draw->get_work());

	}
	else if (this->focus == 11)
	{
		mod->zoom(draw, draw->get_work()->w * 1.1 , draw->get_work()->h * 1.1);
		mod->add_surface(draw->get_work());

	}
	else if (this->focus == 14)
	{
		mod->new_window(draw, screen, this->focus);
		mod->add_surface(draw->get_work());

	}
}



int	controler::event_button(SDL_Surface* screen, model* mod, draw_zone* draw, SDL_Surface* interface)
{
	SDL_Rect	work_pos;


	work_pos = create_position(100, 45, draw->get_work()->w, draw->get_work()->h);
	SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
			SDL_BlitSurface(draw->get_work(), NULL, screen, &work_pos);
	SDL_BlitSurface(interface, NULL, screen, 0);
	SDL_Flip(screen);
	this->work_pos = work_pos;
	while (this->event.type != SDL_QUIT)
	{
		SDL_WaitEvent(&(this->event));
		if (this->event.type == SDL_VIDEORESIZE)
		{
			mod->resize(this->event.resize.w,this->event.resize.h);
			break;
		}
		if (this->event.type == SDL_MOUSEBUTTONDOWN)
		{	
			work_pos = create_position(100, 45, draw->get_work()->w,
			draw->get_work()->h);
			check_button(screen,mod, draw, interface);
			SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
			SDL_BlitSurface(draw->get_work(), NULL, screen, &work_pos);
			SDL_BlitSurface(interface, NULL, screen, 0);
			SDL_Flip(screen);
		}
	}
	return 0;
}



void	controler::get_first_click(model* mod, draw_zone* draw)
{
	while (1)
	{
		SDL_WaitEvent(&(this->event));
		if (this->event.type == SDL_MOUSEBUTTONDOWN)
		{
			mod->set_click1_x(this->event.button.x - 100);
			mod->set_click1_y(this->event.button.y - 35);
			if (this->event.button.y - 35 > draw->get_work()->h)
				mod->set_click1_y(draw->get_work()->h);
			break;
		}
	}
}


void	controler::get_second_click(model* mod, draw_zone* draw)
{
	while (1)
	{
		SDL_WaitEvent(&(this->event));
		if (this->event.type == SDL_MOUSEBUTTONUP)
		{
			mod->set_click2_x(this->event.button.x - 100);
			mod->set_click2_y(this->event.button.y - 35);
			if (this->event.button.y - 35 > draw->get_work()->h)
				mod->set_click2_y(draw->get_work()->h);
			break;
		}
	}
}



