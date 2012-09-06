#include "rectangle.h"

rectangle::rectangle()
{


}

rectangle::~rectangle()
{

}

void	rectangle::init(SDL_Rect* rect)
{
	this->rect = *rect;
}

SDL_Rect*	rectangle::get_rect()
{
	return &(this->rect);
}

