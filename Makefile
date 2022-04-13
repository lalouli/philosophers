# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlalouli <hlalouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 20:10:02 by hlalouli          #+#    #+#              #
#    Updated: 2022/03/26 23:06:55 by hlalouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
INC = philoso.h
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = main.c \
		philo.c \
		utils.c \
		time.c \
		fork.c \
		utils1.c
OBJS = $(SRCS:%.c=%.o)
all:$(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

%.o: %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all