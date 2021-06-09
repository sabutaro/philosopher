# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 11:06:16 by sperrin           #+#    #+#              #
#    Updated: 2021/06/09 10:27:34 by sperrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./srcs
SRCS_BONUS		=	./srcs_bonus
DIR			=	./
PHILO	=	philo
PHILO_BONUS	=	philo_bonus

all:			$(PHILO)

$(PHILO):
				$(MAKE) -C $(SRCS)/$(PHILO)
				@cp -rf $(SRCS)/$(PHILO)/$(PHILO) $(DIR)/$(PHILO)

bonus :
				$(MAKE) -C $(SRCS_BONUS)/$(PHILO_BONUS)
				@cp -rf $(SRCS_BONUS)/$(PHILO_BONUS)/$(PHILO_BONUS) ./$(PHILO_BONUS)

clean:
				make clean -C $(SRCS)/$(PHILO) 
				make clean -C $(SRCS_BONUS)/$(PHILO_BONUS)

fclean:	
				make fclean -C $(SRCS)/$(PHILO)
				make fclean -C $(SRCS_BONUS)/$(PHILO_BONUS)
				rm -rf $(PHILO) 
				rm -rf $(PHILO_BONUS)

re:				fclean all