
NAME = interpret
OBJDIR = obj

HEADERS = $(NAME)Parser.h $(NAME)Parser.ih

all: $(NAME)
	-

$(NAME).yy.cc: $(NAME).l
	flex -o $(NAME).yy.cc $(NAME).l

$(NAME).cc: $(NAME).y
	bisonc++ -f $(NAME)Parser -p $(NAME).cc $(NAME).y

$(NAME): $(NAME).yy.cc $(NAME).cc
	-