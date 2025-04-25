NAME = philo

GCC = gcc -Wall -Wextra -Werror

SRC = 	src/utils/ft_calloc.c \
		src/philo/main.c \
		src/philo/ft_current_time.c \
		src/philo/ft_join_args.c \
		src/utils/ft_split.c \
		src/utils/utils.c \
		src/philo/ft_routine.c \
		src/philo/ft_output.c \
		src/philo/ft_eat.c \
		src/philo/ft_check_dead.c \
		src/philo/ft_parsing.c \
		src/philo/ft_create_philosophers.c \
		src/philo/ft_sleep.c

OBJ = ${SRC:.c=.o}

%.o: %.c philosophers.h
	$(GCC) -c $< -o $@

all: ${NAME}

${NAME}: $(OBJ)
	gcc $(OBJ) -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ${NAME}

re: fclean all
