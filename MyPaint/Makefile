NAME =  id_paint
SRC =   main.cpp\
	colors.cpp\
	controler.cpp\
	model.cpp\
	view.cpp\
	paint.cpp\
	shape.cpp\
	tools.cpp\
	rectangle.cpp\
	empty_rect.cpp\
	button.cpp\
	draw_zone.cpp
OBJ = $(SRC:.cpp=.o)

CPPFLAGS += -Wall -W -Werror -g3


$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -lSDL -lSDL_ttf

clean:
	rm -rf *.o

distclean: clean
	rm -f $(NAME)


rebuild: distclean $(NAME)
