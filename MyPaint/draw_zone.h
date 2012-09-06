#ifndef draw_zone_h
#define draw_zone_h
class draw_zone
{
	public:
		draw_zone();
		~draw_zone();
		int		get_width();
		int		get_height();
		int		get_border_w();
		int		get_border_h();
		void		set_border_w(int);
		void		set_border_h(int);
		SDL_Rect*	get_work_pos();
		SDL_Surface*	get_work();
		void		set_width(int width);
		void		set_height(int height);
		void		set_work_pos(SDL_Rect* rect);
		void		set_work(SDL_Surface* work);


	private:
		int		width;
		int		height;
		int		border_w;
		int		border_h;
		SDL_Rect*	work_pos;
		SDL_Surface*	work;

};

#endif
