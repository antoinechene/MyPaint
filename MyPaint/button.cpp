#include <SDL/SDL.h>
#include "draw_zone.h"
#include "model.h"
#include "tools.h"
#include "model.h"
#include "button.h"

button::button()
{
}

button::~button()
{
}

button::button(SDL_Rect pos, SDL_Surface* im, int type)
{
	this->type = type;
	this->pos = pos;
	this->im = im;
}

void	button::init(SDL_Rect pos, SDL_Surface* im)
{
	this->pos = pos;
	this->im = im;
}

SDL_Surface*	button::get_im()
{
	return (this->im);
}

SDL_Rect*	button::get_pos()
{
	return &(this->pos);
}

void	button::set_im(char* str)
{
	this->im = SDL_LoadBMP(str);
}

int	button::get_type()
{
	return this->type;
}

void	button::set_pos(int x, int y, int w, int h)
{
	this->pos = create_position(x, y, w, h);
}

