# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/19 12:07:11 by sperrin           #+#    #+#              #
#    Updated: 2021/06/10 21:08:36 by sperrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo_bonus
CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./compiled_srcs/

SRC			=	main.c \
				eat_sleep_think.c \
				error.c \
				processus.c \
				dead.c \
				utils.c \

SRCS		=	$(SRC)
OBJS 		=	$(SRCS:%.c=$(DIR_OBJS)%.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) $(OBJS) -o $(NAME) -lpthread

$(OBJS):		| $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c
				$(CC) $(CC_FLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJS):
			mkdir $(DIR_OBJS)

clean:
				rm -rf $(DIR_OBJS)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all