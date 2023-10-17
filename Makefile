# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-malt <ael-malt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/10/17 14:10:24 by ael-malt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #

NAME		= minishell

cc			= cc

CFLAGS		= -Wall -Werror -Wextra -g3

PATH_LIB	= libft

SRC			= src/main.c \
				src/first_check.c \
				src/lst.c\
				src/operator.c \
z				src/env.c \
				src/switch.c \
				src/builtins.c \
				src/util.c \
				src/signal.c \
				src/error.c \
				src/unset.c\
					  src/sup_env.c\
=======
#    Created: 2023/09/19 11:14:11 by lazanett          #+#    #+#              #
#    Updated: 2023/10/17 13:48:02 by ael-malt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
NAME = minishell

cc = cc
cc = cc

CFLAGS = -Wall -Werror -Wextra -g3
CFLAGS = -Wall -Werror -Wextra -g3 -Iinclude #-fsanitize=address,undefined

PATH_LIB = libft
PATH_LIB = libft

SRC = src/main.c\
		src/first_check.c\
		src/lst.c\
		src/operator.c\
		src/env.c\
		src/switch.c\
		src/unset.c\
		src/lst_split.c\
		src/builtins.c \
		src/sup_env.c\
		src/util.c \
LIB = $(PATH_LIB)/libft.a

OBJ = $(SRC:.c=.o)
LIB = $(PATH_LIB)/libft.a
>>>>>>> 9ca6d05 (Merge branch 'main' into amine_dev)

LIB			= $(PATH_LIB)/libft.a

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
