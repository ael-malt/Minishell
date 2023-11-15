# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 13:56:05 by ael-malt          #+#    #+#              #
#    Updated: 2023/11/15 16:16:54 by lazanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

cc			= cc

CFLAGS		= -Wall -Werror -Wextra -g3

PATH_LIB	= libft

SRC			= src/main.c \
				src/first_check.c \
				src/Parsing/1_lst.c\
				src/Parsing/2_operator.c \
				src/Parsing/3_operator_utils.c \
				src/Parsing/4_expand.c \
				src/Parsing/5_switch.c \
				src/Parsing/6_expand_utils.c \
				src/Parsing/7_lst_len_split.c \
				src/Parsing/8_lst_split.c \
				src/Parsing/9_split_redir.c \
				src/Parsing/10_split_redir_utils.c \
				src/Parsing/11_supp_quote.c \
				src/Parsing/12_supp_quote_utils.c \
				src/util.c \
				src/signal.c \
				src/error.c \
				src/get_command.c\
				src/multi_pipe.c \
				src/heredoc.c \
				src/builtins/builtins.c \
				src/builtins/mini_cd.c \
				src/builtins/mini_echo.c \
				src/builtins/mini_exit.c \
				src/builtins/mini_export.c \
				src/builtins/mini_pwd.c \
				src/builtins/mini_unset.c \
				src/redir.c \
				

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
