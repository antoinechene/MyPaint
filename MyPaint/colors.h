#ifndef colors_h
#define colors_h

class colors
{
	public:
		colors();
		~colors();
		void	set_colors(int r, int g ,int b);
		int	get_r();
		int	get_g();
		int	get_b();

	private:
		int	r;
		int	g;
		int	b;

};

#endif
