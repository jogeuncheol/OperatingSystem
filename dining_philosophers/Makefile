NAME = philo

CFLAGS = -Wall -Werror -Wextra # -g3 -fsanitize=address

SRC = ft_main.c\
	  ft_init.c\
	  ft_job_sequence.c\
	  ft_scheduler.c\
	  ft_free.c\
	  ft_detach.c\
	  ft_validation.c\
	  ft_mlibft.c

OBJ = ft_main.o\
	  ft_init.o\
	  ft_job_sequence.o\
	  ft_scheduler.o\
	  ft_free.o\
	  ft_detach.o\
	  ft_validation.o\
	  ft_mlibft.o

all : $(NAME)

$(NAME) : $(OBJ)
	gcc -pthread $(CFLAGS) -o $(NAME) $(OBJ)

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
