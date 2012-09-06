#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "model.h"
class button
{
	public:
		button();
		~button();
		button(SDL_Rect pos, SDL_Surface* im, int type);

		void		init(SDL_Rect, SDL_Surface*);
		SDL_Surface*	get_im();
		SDL_Rect*	get_pos();
		void		set_im(char* str);
		void		set_pos(int x, int y, int w, int h);
		void	exec();
		int	get_type();
	private:
		int		type;
		SDL_Rect	pos;
		SDL_Surface*	im;
};

#endif

