NAME = philo

CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra

SRC = ft_main.c\
	  ft_init.c\
	  ft_job_sequence.c

OBJ = ft_main.o\
	  ft_init.o\
	  ft_job_sequence.o

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -pthread $(CFLAGS) -o $(NAME) $(OBJ)

clean : 
	rm $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all
