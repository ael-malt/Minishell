# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 13:56:05 by ael-malt          #+#    #+#              #
#    Updated: 2023/10/24 17:56:59 by lazanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

cc			= cc

CFLAGS		= -Wall -Werror -Wextra -g3

PATH_LIB	= libft

SRC			= src/main.c \
				src/first_check.c \
				src/lst.c\
				src/lst_split.c \
				src/operator.c \
				src/expand.c \
				src/switch.c \
				src/util.c \
				src/signal.c \
				src/error.c \
				src/unset.c\
				src/get_command.c\
				src/multi_pipe.c \
				src/sup_env.c\
				src/heredoc.c \
				src/builtins/builtins.c \
				src/builtins/mini_cd.c \
				src/builtins/mini_echo.c \
				src/builtins/mini_exit.c \
				src/builtins/mini_export.c \
				src/builtins/mini_pwd.c \
				src/builtins/mini_unset.c \

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
