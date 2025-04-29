# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/29 12:10:03 by calleaum          #+#    #+#              #
#    Updated: 2025/04/29 12:24:21 by calleaum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -pthread

CFLAGS = -g -Wall -Werror -Wextra

RM = rm -rf

SRCS = main.c ft_ato_long.c validation.c init.c error.c time.c \
       output.c garbage_collector.c mutex.c \
       routine_finish.c routine_dining.c

OBJS = $(SRCS:%.c=./obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Build Successful"

./obj/%.o: %.c
	@mkdir -p ./obj
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning objects..."
	@$(RM) ./obj
	@echo "Done!"

fclean: clean
	@echo "Cleaning binaries..."
	@$(RM) $(NAME)
	@echo "Done!"

re: fclean all

.PHONY: all re clean fclean



