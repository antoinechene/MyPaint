#include <SDL/SDL.h>
#include "draw_zone.h"
#include "model.h"
#include "colors.h"
#include "rectangle.h"
#include "empty_rect.h"
#include <math.h>
#include <SDL/SDL_ttf.h>
model::model()
{
	this->resiz = false;
}

model::~model()
{

}

void	model::draw_circle(Uint32 col, draw_zone* draw)
{
	int	r;

	r = sqrt((click1_x - click2_x) * (click1_x - click2_x) + (click1_y - click2_y) * (click1_y - click2_y));
	if (r < 0)
		r = - r;

	int	f = 1 - r;
	int	ddF_x = 1;
	int	ddF_y = -2 * r;
	int	x = 0;
	int	y = r;

	set_pixel(click1_x, click1_y + r, col, draw->get_work());
	set_pixel(click1_x, click1_y - r, col, draw->get_work());
	set_pixel(click1_x + r, click1_y, col, draw->get_work());
	set_pixel(click1_x - r, click1_y, col, draw->get_work());
	while(x < y)
	{
		if(f >= 0) 
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;    
		set_pixel(click1_x + x, click1_y + y, col, draw->get_work());
		set_pixel(click1_x - x, click1_y + y, col, draw->get_work());
		set_pixel(click1_x + x, click1_y - y, col, draw->get_work());
		set_pixel(click1_x - x, click1_y - y, col, draw->get_work());
		set_pixel(click1_x + y, click1_y + x, col, draw->get_work());
		set_pixel(click1_x - y, click1_y + x, col, draw->get_work());
		set_pixel(click1_x + y, click1_y - x, col, draw->get_work());
		set_pixel(click1_x - y, click1_y - x, col, draw->get_work());
	}
}
void	model::draw_disc(Uint32 col, draw_zone* draw)
{

	int	r;
	int	x;
	int	y;
	int height;

	r = sqrt((click1_x - click2_x) *   (click1_x - click2_x) + (click1_y - click2_y) *
	(click1_y - click2_y));
	if (r < 0)
		r = - r;

	x = -r;
	while (x < r)
	{
		height = (int)sqrt(r * r - x * x);
		y = - height;
		while (y < height)
		{
			set_pixel(x + click1_x, y + click1_y, col, draw->get_work());
			y ++;
		}
		x++;
	}
}

char*	model::calcul_res(int n,int expo,char* res)
{
	int i;

	i = 0;
	if (n == 0)
	{
		res[0] =0 + 48;
		return res;
	}
	while (expo >= 1)
	{
		if (n < 0)
		{
			n = - n;
			res[0] = '-';
			i = i + 1;
		 }
		res[i] = n / expo + 48;
		i = i + 1;
		n = n - (n / expo * expo);
		expo = expo / 10;
	}
	res[i] = '\0';
	return res;
}

char*	model::id_itoa(int n)
{
	int expo;
	int ncopy;
	int cpt;
	char* res;

	expo = 1;
	cpt = 0;
	ncopy = n;
	while (ncopy != 0)
	{
		cpt = cpt + 1;
		expo = expo * 10;
		ncopy = ncopy / 10;
	}
	if (n < 0)
		cpt = cpt + 1;
	res = new char[cpt];
	expo = expo / 10;
	res = calcul_res(n, expo, res);
	return res;
}


char*	model::event_clavier(SDL_Event* event, 
			     SDL_Surface* screen, SDL_Rect pos_texte, char* file1, int focus)

{
	SDL_Surface*	texte = NULL;
	SDL_Color	couleur_ttf = {0, 0, 0, 0};
	TTF_Font*	police = NULL;
	int	i;

	printf ("foc %d\n",focus);
	TTF_Init();
	police = TTF_OpenFont("coolvetica rg.ttf", 15);
	i = strlen(file1);
	if (event->type == SDL_KEYDOWN && ((i <= 9 && (focus == 3 || focus == 14))||(i <= 20 && focus == 4) || (i <= 20 && focus == 13) ))
	{
		if (focus == 4 || focus == 13)
		{
			if ((event->key.keysym.sym >= '.' && event->key.keysym.sym <= '9'  ) ||
			    (event->key.keysym.sym >='A' && event->key.keysym.sym <= 'Z') || 
			    (event->key.keysym.sym >= 'a' && event->key.keysym.sym <=
			    'z'))
			{
				file1[i] = event->key.keysym.sym;
				file1[i + 1] = 0;
				texte = TTF_RenderText_Blended(police, file1, couleur_ttf);
				SDL_BlitSurface(texte, NULL, screen, &pos_texte);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
			}
		}
		else if (focus == 3 || focus == 14)
		{
			if (event->key.keysym.sym >= '0' && event->key.keysym.sym <= '9'  )
				file1[i] = event->key.keysym.sym;
				file1[i + 1] = 0;
				texte = TTF_RenderText_Blended(police, file1, couleur_ttf);
				SDL_BlitSurface(texte, NULL, screen, &pos_texte);
				SDL_UpdateRect(screen, 0, 0, 0, 0);
		}
	}
	TTF_CloseFont(police);
	return (file1);
}

void	model::pop_up(const char* filename, draw_zone* draw, SDL_Surface* screen)
{

	SDL_Rect	pcopy;
	SDL_Surface*	copy = NULL;
	SDL_Rect	pos_win_new;
	SDL_Surface*	win_new = NULL;


	pcopy = create_position(100, 45, 0, 0);
	copy = SDL_CreateRGBSurface(SDL_HWSURFACE, draw->get_work()->clip_rect.w,
				    draw->get_work()->clip_rect.h, 32, 0, 0, 0, 0);
	SDL_BlitSurface(draw->get_work(), NULL, copy, NULL);
	pos_win_new = create_position(200, 140, 0, 0);
	win_new = SDL_LoadBMP(filename);
	SDL_BlitSurface(win_new, NULL, screen, &pos_win_new);
	SDL_UpdateRect(screen, 0, 0, 0, 0);


}

void	model::new_window(draw_zone* draw, SDL_Surface* screen, int focus)
{
	SDL_Event	event;
	SDL_Surface*	win_new = NULL;
	SDL_Surface*	test = NULL;
	SDL_Rect	test2;
	SDL_Surface*	copy = NULL;
	SDL_Rect	pos_texte;
	int		button;
	char*		file1 = new char[50];
	char*		file2 = new char[10];

	file2[0] = '\0';
	file1[0] = '\0';
	button = 0;
	if (focus == 3)
		this->pop_up("./images/menu_new.bmp", draw, screen);
	else if (focus == 4)
		this->pop_up("./images/menu_save.bmp", draw, screen);
	else if (focus == 13)
		this->pop_up("./images/menu_open.bmp", draw, screen);
	else if (focus == 14)
		this->pop_up("./images/menu_resize.bmp", draw, screen);

	while (1)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.y >= 282 && event.button.y <= 308 &&
			    event.button.x >= 424 && event.button.x <= 521)
			{
				if (focus == 3)
				{
					this->nb_redo = 0;
					SDL_FreeSurface(win_new);
					test = SDL_CreateRGBSurface(SDL_HWSURFACE, atoi(file1), atoi(file2), 32, 0, 0, 0, 0);
					draw->set_width(atoi(file1));
					draw->set_height(atoi(file2));
					if (draw->get_height() > 10000 || draw->get_width() > 10000)
						break;
					draw->set_work(test);
					draw->set_work_pos(&test2);
					SDL_FillRect(draw->get_work(), NULL, SDL_MapRGB(draw->get_work()->format, 255, 255, 255));
					SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
				}
				if (focus == 4)
				{
					strcat(file1,".bmp");
					SDL_SaveBMP(draw->get_work(), file1);
					SDL_FreeSurface(win_new);
					SDL_BlitSurface(copy, NULL, draw->get_work(), 0);
					SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
				}

				if (focus == 13)
				{
					test = SDL_LoadBMP(file1);
					if (test == NULL)
					{
						printf("error during file loading\n");
						break;
					}
					draw->set_work(test);
					SDL_FreeSurface(win_new);
					SDL_BlitSurface(copy, NULL, draw->get_work(), 0);
					SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
				}

				if (focus == 14)
				{
					this->zoom(draw,atoi(file1),atoi(file2));
					SDL_FreeSurface(win_new);
					SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
				}
				break;
			}
			if ((event.button.y >= 142 && event.button.y <= 156 &&
			     event.button.x >= 212 && event.button.x <= 225) ||
			    (event.button.y >= 283 && event.button.y <= 308 &&
			    event.button.x >= 319 && event.button.x <= 415))
			{
				SDL_FreeSurface(win_new);
				SDL_BlitSurface(copy, NULL, draw->get_work(), 0);
				SDL_FillRect(screen, NULL, SDL_MapRGB(draw->get_work()->format, 125, 125, 125));
				break;
			}
			if (focus == 4 || focus == 13)
			{
				if (event.button.y >= 195 && event.button.y <= 218 &&
				   event.button.x >= 290 && event.button.x <= 502)
				{
					button = 0;
					pos_texte = create_position(290, 200, 0, 0);
				}
			}
			if (focus == 3 || focus == 14)
			{

				if (event.button.y >= 195 && event.button.y <= 218 &&
				   event.button.x >= 290 && event.button.x <= 364)
				{
					button = 0;
					pos_texte = create_position(290, 200, 0, 0);
				}
				if (event.button.y >= 224 && event.button.y <= 290 &&
				   event.button.x >= 290 && event.button.x <= 364)
				{
					button = 1;
					pos_texte = create_position(290, 229, 0, 0);
				}
			}
		}


		if (button == 0)
			event_clavier(&event, screen, pos_texte, file1, focus);
		else
			event_clavier(&event, screen, pos_texte, file2,focus);
	}
	delete [] file1;
	delete [] file2;
	TTF_Quit();
}



void	model::verif_rect(draw_zone* draw)
{
	if (this->click1_x > draw->get_work()->w - draw->get_border_w())
		this->click1_x = draw->get_work()->w - draw->get_border_w();
	if (this->click2_x > draw->get_work()->w - draw->get_border_w())
		this->click2_x = draw->get_work()->w - draw->get_border_w();
	if (this->click1_y >draw->get_work()->h - draw->get_border_h())
		this->click1_y = draw->get_work()->h - draw->get_border_h();
	if (this->click2_y > draw->get_work()->h - draw->get_border_h())
		this->click2_y = draw->get_work()->h - draw->get_border_h();
}


void	model::draw_full_rect(draw_zone* draw, Uint32 color)
{
	rectangle*	rect;

	rect = new rectangle();

	this->verif_rect(draw);
	this->check_side1(rect->get_rect());
	this->check_side2(rect->get_rect());
	this->check_side3(rect->get_rect());
	this->check_side4(rect->get_rect());
	SDL_FillRect(draw->get_work(), rect->get_rect(), color);
}

int	model::get_click1_x()
{
	return this->click1_x;
}
void	model::add_surface (SDL_Surface*  draw)
{
	SDL_Surface*	copy = NULL;


	copy = SDL_CreateRGBSurface(SDL_HWSURFACE, draw->clip_rect.w,
				    draw->clip_rect.h, 32, 0, 0, 0, 0);

	this->nb_redo = 1;
	SDL_BlitSurface(draw, NULL, copy, NULL);
	this->undos.push_back(copy);
}

int	model::get_click1_y()
{
	return this->click1_y;

}
int	model::get_click2_x()
{
	return this->click2_x;

}
int	model::get_click2_y()
{
	return this->click2_y;

}
void	model::set_click1_x(int x)
{
	this->click1_x = x;
}
void	model::set_click1_y(int y)
{
	this->click1_y = y;
}
void	model::set_click2_x(int x)
{
	this->click2_x = x;
}
void	model::set_click2_y(int y)
{
	this->click2_y = y;
}

void	model::set_resize(bool value)
{
	this->resiz = value;
}
bool	model::get_resize()
{
	return this->resiz;
}
int	model::get_resize_x()
{
	return this->resize_x;
}
int	model::get_resize_y()
{
	return this->resize_y;
}
void	model::check_side1(SDL_Rect* r)
{
	if (this->click1_x <= this->click2_x && this->click1_y <= this->click2_y)
	{
		r->x = this->click1_x;
		r->y = this->click1_y;
		r->w = this->click2_x - this->click1_x;
		r->h = this->click2_y - this->click1_y;
	}
}

void	model::check_side2(SDL_Rect* r)
{
	if (this->click1_x >= this->click2_x && this->click1_y >= this->click2_y)
	{
		r->x = this->click2_x;
		r->y = this->click2_y;
		r->w = this->click1_x - this->click2_x;
		r->h = this->click1_y - this->click2_y;
	}
}

void	model::check_side3(SDL_Rect* r)
{
	if (this->click1_x <= this->click2_x && this->click1_y >= this->click2_y)
	{
		r->x = this->click1_x;

		r->y = this->click2_y;
		r->w = this->click2_x - this->click1_x;
		r->h = this->click1_y - this->click2_y;
	}
}

void	model::check_side4(SDL_Rect* r)
{
	if (this->click1_x >= this->click2_x && this->click1_y <= this->click2_y)
	{
		r->x = this->click2_x;
		r->y = this->click1_y;
		r->w = this->click1_x - this->click2_x;
		r->h = this->click2_y - this->click1_y;
	}
}

void	model::draw_empty_rect(draw_zone* draw, Uint32 col)
{
	size_t	x;
	size_t	y;
	size_t	w;
	size_t	h;
	SDL_Rect	r;
	empty_rect*	rect;

	rect = new empty_rect();

	this->verif_rect(draw);
	this->check_side1(&r);
	this->check_side2(&r);
	this->check_side3(&r);
	this->check_side4(&r);
	x = r.x;
	y = r.y;
	w = r.w;
	h = r.h;
	if (h <= 1)
		h = 2;
	rect->set_empty_rect(x, y, w, 1, rect->get_side1());
	rect->set_empty_rect(x, y + h - 1, w, 1, rect->get_side2());
	rect->set_empty_rect(x, y + 1, 1, h - 2, rect->get_side3());
	rect->set_empty_rect(x + w - 1, y + 1, 1, h - 2, rect->get_side4());
	SDL_FillRect(draw->get_work(), rect->get_side1(), col);
	SDL_FillRect(draw->get_work(), rect->get_side2(), col);
	SDL_FillRect(draw->get_work(), rect->get_side3(), col);
	SDL_FillRect(draw->get_work(), rect->get_side4(), col);
	return;
}

void	model::set_pixel(int x, int y, Uint32 col, SDL_Surface* surface)
{
	if (x > 0 && x < surface->w && y < surface->h && y > 0)
		*((Uint32*)(surface->pixels) + x + y * surface->w) = col;
}

Uint32	model::get_pixel(int x, int y, SDL_Surface* screen)
{
	Uint32*	pixel;

	pixel = (Uint32*)screen->pixels;
	return (pixel[(y * screen->w) + x]);
}

void	model::flood_fill(int x, int y, Uint32 color, draw_zone* draw)
{
	SDL_Rect		pix;
	std::vector<SDL_Rect>	pile;
	int			xmax;
	Uint32			colcible;

	pix.x = x;
	pix.y = y;
	colcible = this->get_pixel(x, y, draw->get_work());
	if (color == colcible)
		return;
	pile.push_back(pix);
	while (pile.begin() != pile.end())
	{
		pix = pile.back();
		pile.pop_back();
		if (this->get_pixel(pix.x, pix.y, draw->get_work()) == colcible)
		{ 
			xmax = pix.x;
			while (pix.x > 0 && this->get_pixel(pix.x, pix.y, draw->get_work()) == colcible)
				pix.x--;
			pix.x++;
			while (xmax < draw->get_work()->w && this->get_pixel(xmax, pix.y, draw->get_work()) == colcible)
				xmax++;
			xmax--;
			while (pix.x <= xmax)
			{
				this->set_pixel(pix.x, pix.y, color, draw->get_work());
				if (pix.y > 0 && this->get_pixel(pix.x, pix.y - 1, draw->get_work()) == colcible)
				{
					pix.y--;
					pile.push_back(pix);
					pix.y++;
				}
				if (pix.y < draw->get_work()->h && this->get_pixel(pix.x, pix.y + 1, draw->get_work()) == colcible)
				{
					pix.y++;
					pile.push_back(pix);
					pix.y--;
				}
				pix.x++;
			}
		}
	}
}

void	model::resize(int x, int y)
{
	this->resiz = true;
	this->resize_x = x;
	this->resize_y = y;
}

void	model::circular_brush(Uint32 col, draw_zone* draw, SDL_Surface* screen)
{
	int	r;
	int	x;
	int	y;
	int	height;

	SDL_Rect	work_pos;

	work_pos = create_position(100, 45, draw->get_work()->w, draw->get_work()->h);


	r = 10;
	if (r < 0)
		r = - r;
	x = -r;
	while (x < r)
	{
		height = (int)sqrt(r * r - x * x);
		y = - height;
		while (y < height)
		{
			set_pixel(x + click1_x, y + click1_y, col, draw->get_work());
			y ++;
		}
		x++;
	}
	SDL_BlitSurface(draw->get_work(), NULL, screen, &work_pos);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void model::zoom(draw_zone* draw, int x , int y)
{
	SDL_Surface*	test;
	int		new_width;
	int		new_height;
	SDL_Rect	test2;

	test2= create_position(100, 35 , x, draw->get_work()->h);
	new_width = x ;
	new_height = y ;
	test = SDL_CreateRGBSurface(SDL_HWSURFACE, x  , y  , 32, 0, 0, 0, 0);
	SDL_FillRect(test, NULL, SDL_MapRGB(draw->get_work()->format, 255, 255, 255));

	while (y > 0)
	{
		y --;

		while (x > 0)
		{
			x--;
			set_pixel(x, y, get_pixel(x * draw->get_work()->w / new_width, y *
			draw->get_work()->h / new_height, draw->get_work()), test);  
		}
		x = new_width;
	}
	draw->set_work_pos(&test2);
	draw->set_work(test);
}

void	model::undo(draw_zone* draw)
{

	printf("redo %d size %d\n",this->nb_redo  ,this->undos.size() -1 );
	if (this->nb_redo  < this->undos.size() - 1 )
	{
		printf("plouf\n");
		draw->set_work( undos[this->undos.size() -1 - this->nb_redo ]);
	this->nb_redo ++;

	}
	else
		return;

}

