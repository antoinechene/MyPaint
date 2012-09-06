#include "colors.h"


colors::colors()
{
}

colors::~colors()
{

}

void	colors::set_colors(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

int	colors::get_r()
{
	return this->r;
}

int	colors::get_g()
{
	return this->g;
}

int	colors::get_b()
{
	return this->b;
}


