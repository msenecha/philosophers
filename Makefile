# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 13:58:22 by msenecha          #+#    #+#              #
#    Updated: 2023/09/19 12:05:32 by msenecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
################################### ARGUMENTS #################################

NAME			= philo
CC				= gcc
FLAGS 			= -g -Wall -Wextra -Werror
FSANITIZE		= -fsanitize=address -g3
LIB				= -lpthread
INCLUDES		= -I$(HEADERS_DIR)

###############################################################################
################################### SOURCES ###################################

HEADERS_DIR		= ./includes/

SRC				= main.c utils.c init.c routine.c monitoring.c

OBJECTS			= $(SRC:.c=.o)

###############################################################################
################################### RULES #####################################

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(INCLUDES) $(OBJECTS) $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all libft clean fclean re
