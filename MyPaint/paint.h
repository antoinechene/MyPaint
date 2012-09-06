#ifndef paint_h
#define paint_h
#include <SDL/SDL.h>
#include "draw_zone.h"
#include "button.h"
#include "model.h"
#include "controler.h"
#include "view.h"

class paint
{
	public:
		paint();
		~paint();
		model*		get_model();
		view*		get_view();
		controler*	get_controler();
	private:
		model*		mod;
		view*		vi;
		controler*	control;

};

#endif
