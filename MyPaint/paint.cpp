
#include "paint.h"


paint::paint()
{
	this->mod = new model();
	this->vi = new view();
	this->control = new controler();
	this->control->init();

}

paint::~paint()
{
	SDL_Quit();
	delete mod;
	delete vi;
	delete control;
}

model*	paint::get_model()
{
	return this->mod;
}
view*	paint::get_view()
{
	return this->vi;
}
controler*	paint::get_controler()
{
	return this->control;
}
