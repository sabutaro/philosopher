# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 10:54:49 by sperrin           #+#    #+#              #
#    Updated: 2021/06/14 13:15:09 by sperrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo
CC			=	gcc
CC_FLAGS	=	-Wall -Wextra -Werror
DIR_HEADERS =	./includes/
DIR_SRCS	=	./srcs/
DIR_OBJS	=	./compiled_srcs/

SRC			=	main.c \
				error_and_free.c \
				utils.c \
				eat_sleep_think.c \
				dead.c

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