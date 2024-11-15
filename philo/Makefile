# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdella-r <mdella-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 14:03:57 by mdella-r          #+#    #+#              #
#    Updated: 2024/05/18 10:36:10 by mdella-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c routine.c utils.c utils_II.c
OBJS = $(SRCS:.c=.o)
INCLUDES = .
HEADERS = philo.h
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
		@echo compiled $(NAME)

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
		@$(RM) $(OBJS)
		@echo removed object files

fclean: clean
		@$(RM) $(NAME)
		@echo removed $(NAME)

re: fclean all

.PHONY: all clean fclean re