#include <SDL/SDL.h>
#include <unistd.h>
#include "tools.h"
#include "draw_zone.h"

draw_zone::draw_zone()
{
}

draw_zone::~draw_zone()
{
}

int	draw_zone::get_width()
{
	return this->width;
}

int	draw_zone::get_height()
{
	return this->height;
}

SDL_Rect*	draw_zone::get_work_pos()
{
	return (this->work_pos);
}
SDL_Surface*	draw_zone::get_work()
{
	return (this->work);
}


void	draw_zone::set_width(int width)
{
	this->width = width;
}

void	draw_zone::set_height(int height)
{
	this->height = height;
}
void	draw_zone::set_work_pos(SDL_Rect* work_pos)
{
	this->work_pos = work_pos;
}
void	draw_zone::set_work(SDL_Surface* work)
{	
	SDL_FreeSurface(this->work); 
	this->work = work;
}

int	draw_zone::get_border_w()
{
	return this->border_w;
}

int	draw_zone::get_border_h()
{
	return this->border_h;
}

void	draw_zone::set_border_w(int width)
{
	this->border_w = width;
}

void	draw_zone::set_border_h(int height)
{
	this->border_h = height;
}
