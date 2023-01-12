SRCS =  	main.c \
			error_handling.c \
			philosophers.c	\
			utils.c \
			init.c \
			destroy.c \
			utils_thread.c \
			check_death.c	

OBJ = 		main.o \
			error_handling.o \
			philosophers.o	\
			utils.o \
			init.o \
			destroy.o \
			utils_thread.o \
			check_death.o	

CC = gcc -Wall -Werror -Wextra -g 

NAME = philo.a

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	gcc -o philo $(NAME) -lpthread

$(OBJS) :
	$(CC) -c $(SRCS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -rf $(NAME)
	rm -rf philo

run :
	valgrind --tool=helgrind ./philo 3 100 300 600
re : fclean all

.phony : fclean all re clean
