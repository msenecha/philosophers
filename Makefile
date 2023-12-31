# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msenecha <msenecha@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 13:58:22 by msenecha          #+#    #+#              #
#    Updated: 2023/10/07 18:46:47 by msenecha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############################################################################
################################### ARGUMENTS #################################

NAME			= philo
CC				= gcc
FLAGS 			= -g -Wall -Wextra -Werror
FSANITIZE		= -fsanitize=thread -g3
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
	@$(CC) $(INCLUDES) $(OBJECTS) $(LIB) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
