#include <SDL/SDL.h>
#include "draw_zone.h"
#include "button.h"
#include "controler.h"
#include "view.h"

view::view()
{
	this->screen = NULL;
	this->draw = new draw_zone();
	this->interface = NULL;
	this->pos_inter.x = 0;
	this->pos_inter.y = 0;
}

view::~view()
{
	delete this->screen;
	delete this->draw;
}

draw_zone*	view::get_draw_zone()
{
	return this->draw;
}


SDL_Surface*	view::get_screen()
{
	return this->screen;
}
int	view::create_box()
{
	SDL_Surface*	bas = NULL;
	SDL_Rect	position_bas;
	SDL_Surface*	verti = NULL;
	SDL_Rect	position_verti;
	SDL_Rect	pos;
	SDL_Surface*	haut = NULL;

	haut = SDL_LoadBMP("./images/haut.bmp");
	position_bas = create_position(0, this->height -  100, 0, 0);
	bas = SDL_LoadBMP("./images/bas.bmp");
	position_verti = create_position(0, 0, 0, 0);
	verti = SDL_LoadBMP("./images/verti.bmp");
	SDL_BlitSurface(verti, NULL, this->interface, &position_verti);
	SDL_BlitSurface(bas, NULL, this->interface, &position_bas);
	SDL_BlitSurface(haut, NULL, this->interface, &position_verti);
	
	pos = create_position(45, this->screen->h - 90, 30, 30);
	SDL_FillRect(this->interface, &pos, SDL_MapRGB(this->interface->format, 255, 255, 255));
	
	pos = create_position(45, this->screen->h - 50 , 30, 30);
	SDL_FillRect(this->interface, &pos, SDL_MapRGB(this->interface->format, 0, 0, 0));
	SDL_BlitSurface(this->interface, NULL, this->screen, &pos_inter);


	SDL_Flip(screen);

	return 0;
}


int	view::create_button_color(controler* control)
{
	int	i;
	int	j;
	int	x;
	int	y;
	SDL_Rect	pos;
	SDL_Surface*	im;

	im = SDL_LoadBMP("./images/couleurs.bmp");
	pos = create_position(100, this->height - 90, 0, 0);
	i = 0;
	j = 0;
	x = 109;
	y = this->height - 82;
	SDL_BlitSurface(im, NULL, this->interface, &pos);
	while (i < 2)
	{
		while (j < 8)
		{
			control->add_button(new button(create_position(x, y, 0, 0),
					   NULL, 0));
			j ++ ;
			x = x + 39;
		}
		i ++;
		j = 0;
		x = x - (39 * 8);
		y = y + 35;
	}
	SDL_BlitSurface(interface, NULL, this->screen, &pos_inter);

	return 0;
}

int	view::init_window()
{
	SDL_Rect	pos;

	this->draw->set_work(SDL_CreateRGBSurface(SDL_HWSURFACE, this->width - 100, this->height - 145, 32,
						0, 0, 0, 0));

	this->draw->set_width(this->width - 100);
	this->draw->set_height(this->height - 145);
	pos.x = 100;
	pos.y = 45;
	pos.w = this->width - 100;
	pos.h = this->height - 145;
	this->draw->set_work_pos(&pos);

	this->interface = (SDL_CreateRGBSurface(SDL_HWSURFACE, this->width , this->height, 32,
							0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));

	SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_WM_SetCaption("id_paint", NULL);
	this->screen = SDL_SetVideoMode(this->width, this->height, 32, SDL_RESIZABLE);
	SDL_BlitSurface(this->interface, NULL, this->screen, &pos_inter);

	return 0;
}
int	view::create_button_tools(controler* control)
{
	button*		rectangle;
	button*		empty_rect; 
	button*		pipette;
	button*		circle;
	button*		flood_fill;
	button*		disc;
	button*		brush;
	button*		zoom_out;
	button*		zoom_in;

	pipette =  new button(create_position(10, 140, 0, 0), SDL_LoadBMP("./images/pipette.bmp"), 5);
	rectangle = new button(create_position(50, 100, 0, 0), SDL_LoadBMP("./images/boutton_carre.bmp"), 1);
	empty_rect = new button(create_position(10 , 100, 0, 0), SDL_LoadBMP("./images/boutton_carre_vide.bmp"), 2);
	circle = new button(create_position(10 , 180, 0, 0), SDL_LoadBMP("./images/cercle.bmp"), 7);
	flood_fill = new button(create_position(50 , 140, 0, 0), SDL_LoadBMP("./images/pot_peinture.bmp"), 6);
	disc = new button(create_position(50, 180, 0, 0), SDL_LoadBMP("./images/disc.bmp"), 8);
	brush = new button(create_position(10, 220, 0, 0), SDL_LoadBMP("./images/brush.bmp"), 9);
	zoom_out = new button(create_position(50, 260, 0, 0), SDL_LoadBMP("./images/zoom_out.bmp"), 10);
	zoom_in = new button(create_position(10, 260, 0, 0), SDL_LoadBMP("./images/zoom_in.bmp"), 11);

	
	SDL_BlitSurface(rectangle->get_im(), NULL, this->interface, rectangle->get_pos());
	SDL_BlitSurface(empty_rect->get_im(), NULL, this->interface, empty_rect->get_pos());
	SDL_BlitSurface(pipette->get_im(), NULL, this->interface, pipette->get_pos());
	SDL_BlitSurface(circle->get_im(), NULL, this->interface, circle->get_pos());
	SDL_BlitSurface(flood_fill->get_im(), NULL, this->interface, flood_fill->get_pos());
	SDL_BlitSurface(disc->get_im(), NULL, this->interface, disc->get_pos());
	SDL_BlitSurface(brush->get_im(), NULL, this->interface, brush->get_pos());
	SDL_BlitSurface(zoom_out->get_im(), NULL, this->interface, zoom_out->get_pos());
	SDL_BlitSurface(zoom_in->get_im(), NULL, this->interface, zoom_in->get_pos());


	control->add_button(pipette);
	control->add_button(rectangle);
	control->add_button(empty_rect);
	control->add_button(circle);
	control->add_button(flood_fill);
	control->add_button(disc);
	control->add_button(brush);
	control->add_button(zoom_out);
	control->add_button(zoom_in);


	SDL_BlitSurface(this->interface, NULL, this->screen, &pos_inter);


	return 0;
}

int	view::button_menu(controler* control)
{
	button*	button_new;
	button*	button_save;
	button*	button_open;
	button*	button_resize;


	button_new = new button(create_position(100, 7, 0, 0), SDL_LoadBMP("./images/new.bmp"), 3);
	button_save = new button(create_position(140, 7, 0, 0), SDL_LoadBMP("./images/save.bmp"), 4);

	button_open = new button(create_position(180, 7, 0, 0), SDL_LoadBMP("./images/openfile.bmp"), 13);

	button_resize = new button(create_position(220, 7, 0, 0), SDL_LoadBMP("./images/resize.bmp"), 14);


	control->add_button(button_new);
	control->add_button(button_save);
	control->add_button(button_open);
	control->add_button(button_resize);


	SDL_BlitSurface(button_new->get_im(), NULL, this->interface, button_new->get_pos());
	SDL_BlitSurface(button_save->get_im(), NULL, this->interface, button_save->get_pos());

	SDL_BlitSurface(button_open->get_im(), NULL, this->interface, button_open->get_pos());
	SDL_BlitSurface(button_resize->get_im(), NULL, this->interface, button_resize->get_pos());

	SDL_BlitSurface(this->interface, NULL, this->screen, &pos_inter);

	return 0;

}

void	view::init_color_used(controler* control)
{
	control->set_color_leftc(SDL_MapRGB(this->screen->format, 255, 255, 255));
	control->set_color_rightc(SDL_MapRGB(this->screen->format, 0, 0, 0));
}
int	view::create_interface(controler* control, int width, int height)
{
	this->width = width;
	this->height = height;
	this->init_window();
	this->create_box();
	this->create_button_color(control);
	this->create_button_tools(control);
	this->button_menu(control);

	this->init_color_used(control);
	SDL_Flip(this->screen);

	return 0;
}

SDL_Surface*	view::get_interface()
{
	return this->interface;
}
SDL_Rect*	view::get_pos_inter()
{
	return &this->pos_inter;
}

