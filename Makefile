# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrilles <atrilles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 17:07:37 by atrilles          #+#    #+#              #
#    Updated: 2022/07/20 15:48:16 by atrilles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

######## PROJECT ###############################################################

NAME = philo

######## DIRECTORIES ###########################################################

SRC_DIR	= src/

######## SOURCE FILES ##########################################################

SRC_FILES =		philo	functions	states	init	time

SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))

######## FLAGS #################################################################

CC = gcc
CFLAGS = -Wall -Wextra -Werror

######## RULES #################################################################

all: $(NAME)

$(NAME): $(OBJ)
#MAC	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

%.o: %.c
#MAC	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -lpthread -c $< -o $@


.PHONY: clean fclean re

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
