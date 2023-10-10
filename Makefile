# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 11:14:11 by lazanett          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/10/10 14:07:31 by ael-malt         ###   ########.fr        #
=======
#    Updated: 2023/10/10 12:54:47 by lazanett         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME		= minishell

cc			= cc

CFLAGS		= -Wall -Werror -Wextra -g3

PATH_LIB	= libft

<<<<<<< HEAD
SRC			= src/main.c \
				src/first_check.c\
				src/tree.c\
				src/operator.c\
				src/env.c\
				src/switch.c \
				src/builtins.c \
				src/util.c \
				src/signal.c \
				src/error.c \
				
LIB			= $(PATH_LIB)/libft.a
=======
SRC = src/main.c\
	  src/first_check.c\
	  src/tree.c\
	  src/operator.c\
	  src/env.c\
	  src/switch.c\
	  src/unset.c\
>>>>>>> main

OBJ			= $(SRC:.c=.o)

all : $(LIB) $(NAME)

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) -lreadline
	@echo "\n Compilation OK\n"

.c.o :
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB) :
	@make -s -C $(PATH_LIB)

clean :
	@make -s -C $(PATH_LIB) fclean
	@ rm -f $(OBJ) 

fclean : clean
	@make -s -C $(PATH_LIB) fclean 
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
