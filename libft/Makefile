# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 12:03:41 by lazanett          #+#    #+#              #
#    Updated: 2023/06/28 16:50:44 by lazanett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = include/libft.h

CC = cc

RM = bin/rm -f

CFLAGS = -Wall -Wextra -Werror

SRCS = src/ft_isalnum.c \
       src/ft_isalpha.c \
       src/ft_isascii.c \
       src/ft_isdigit.c \
       src/ft_isprint.c \
       src/ft_toupper.c \
       src/ft_tolower.c \
       src/ft_strncmp.c \
       src/ft_memcmp.c \
       src/ft_atoi.c \
       src/ft_strlcat.c \
       src/ft_strlcpy.c \
       src/ft_strlen.c \
       src/ft_calloc.c \
       src/ft_memset.c\
       src/ft_bzero.c \
       src/ft_memcpy.c \
       src/ft_memmove.c \
       src/ft_memchr.c \
       src/ft_strnstr.c \
       src/ft_strchr.c \
       src/ft_strrchr.c \
       src/ft_strdup.c \
       src/ft_strjoin.c \
       src/ft_strjoin1.c \
       src/ft_substr.c \
       src/ft_strtrim.c \
       src/ft_strmapi.c \
       src/ft_split.c \
       src/ft_itoa.c \
       src/ft_striteri.c \
       src/ft_putchar_fd.c \
       src/ft_putstr_fd.c \
       src/ft_putendl_fd.c \
       src/ft_putnbr_fd.c \
       src/ft_lstnew.c\
       src/ft_lstadd_front.c\
       src/ft_lstsize.c\
       src/ft_lstlast.c\
       src/ft_lstadd_back.c\
       src/ft_lstdelone.c\
       src/ft_lstclear.c\
       src/ft_lstiter.c\
       src/ft_lstmap.c\
       src/ft_print_nbr.c \
       src/ft_hexa_size.c\
       src/ft_put_hexa.c\
       src/ft_print_hexa.c\
       src/ft_printf.c\
       src/ft_put_u.c\
       src/ft_putchar.c\
       src/ft_putstr.c\
       src/ft_void_hexa.c\
       src/get_next_line.c\
       src/get_next_line_utils.c \
       src/ft_free.c\
       src/ft_perror.c\

OBJS	= ${SRCS:.c=.o}

$(NAME) : ${OBJS}
	ar rc ${NAME} ${OBJS}

all:	${NAME}

clean :
	@/bin/rm -f ${OBJS}

fclean : clean
	@/bin/rm -f ${NAME}

re : fclean all

.o .c:
	@cc -Wall -Werror -Wextra -c $< -o ${<:.c = .o}

.PHONY:
	all re clean fclean 
