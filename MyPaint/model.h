#ifndef model_h
#define model_h
#include <SDL/SDL.h>
#include <unistd.h>
#include "tools.h"
#include <iostream>
#include <vector>
#include "draw_zone.h"

class model
{
	public:
		model();
		~model();
		void	verif_rect(draw_zone* draw);
		void	draw_full_rect(draw_zone* draw, Uint32 col);
		void	draw_empty_rect(draw_zone* draw, Uint32 col);
		void	draw_circle(Uint32 col, draw_zone* draw);
		void	check_side1(SDL_Rect* r);
		void	check_side2(SDL_Rect* r);
		void	check_side3(SDL_Rect* r);
		void	check_side4(SDL_Rect* r);
		void	set_click1_x(int x);
		void	set_click1_y(int y);
		void	set_click2_x(int x);
		void	set_click2_y(int x);
		void	set_resize(bool value);
		int	get_resize_x();
		int	get_resize_y();
		bool	get_resize();
		int	get_click1_x();
		int	get_click1_y();
		int	get_click2_x();
		int	get_click2_y();
		Uint32	get_pixel(int x, int y, SDL_Surface* screen);
		void	set_pixel(int x, int y, Uint32 col, SDL_Surface* surface);
		void	flood_fill(int x, int y, Uint32 color, draw_zone* draw);
		void	resize(int x, int y);
		void	draw_disc(Uint32 col, draw_zone* draw);
		void	circular_brush(Uint32 col, draw_zone* draw, SDL_Surface* screen);
		void	zoom(draw_zone* draw, int x, int y);
		char*	calcul_res(int n,int expo,char* res);
		char*	id_itoa(int n);
		char*	event_clavier(SDL_Event* event,SDL_Surface* screen,SDL_Rect
		pos_texte, char* number1,int focus);
		void	new_window(draw_zone* draw, SDL_Surface*
		screen,int focus);
		void	pop_up(const char* filename,draw_zone* draw,SDL_Surface* screen);



void	add_surface(SDL_Surface* draw);
void	undo(draw_zone* draw);


	private:
		std::vector<SDL_Surface*> undos;
		size_t		nb_redo;
		bool		resiz;
		int		resize_x;
		int		resize_y;
		int		click1_x;
		int		click1_y;
		int		click2_x;
		int		click2_y;
};

#endif
