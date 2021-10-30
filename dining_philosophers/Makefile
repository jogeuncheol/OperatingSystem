NAME = philo

CFLAGS = -g3 -fsanitize=address -Wall -Werror -Wextra

SRC = ft_main.c\
	  ft_init.c\
	  ft_job_sequence.c\
	  ft_scheduler.c

OBJ = ft_main.o\
	  ft_init.o\
	  ft_job_sequence.o\
	  ft_scheduler.o

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -pthread $(CFLAGS) -o $(NAME) $(OBJ)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
