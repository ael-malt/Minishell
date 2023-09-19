# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 11:14:11 by lazanett          #+#    #+#              #
#    Updated: 2023/09/19 11:16:34 by lazanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

cc = cc

CFLAGS = -Wall -Werror -Wextra

SRC = src/main.c\
	  src/parsing.c\

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n Compilation OK\n"

.c.o :
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@ rm -f $(OBJ) 

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
