/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lazanett <lazanett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:51:25 by lazanett          #+#    #+#             */
/*   Updated: 2023/07/20 14:49:33 by lazanett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
//# include <bsd/string.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <errno.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

long long	ft_atoi(const char *nptr);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_print_nbr(unsigned int n);
int			ft_hexa_size(unsigned int n);
int			ft_put_hexa(unsigned int n, const char flag);
int			ft_print_hexa(unsigned int n, const char flag);
int			ft_printf(const char *s, ...);
int			ft_execut_flag(const char flag, va_list a);
int			ft_len_u(unsigned int u);
int			ft_put_u(unsigned int i);
int			ft_putchar(int c);
int			ft_putpourcent(void);
int			ft_putstr(char *s);
int			hexavoid_len(uintptr_t n);
int			ft_put_hexavoid(uintptr_t n);
int			ft_print_voidtohexa(unsigned long long n);
int			ft_lstsize(t_list *lst);
int			ft_reschr(char *res);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_strlen1(char *s);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		ft_free(char **free_me);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strdup(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strjoin1(char *s1, char *s2);
char		*get_next_line(int fd);
char		*ft_read_line(int fd, char *line, char *buf);
char		*ft_check_line(char *line);
char		*ft_getlast_line(char *line, char *buf);
char		*ft_strjoin_gnl(char *line, char *buf);
char		*ft_strchr_gnl(char *line, int c);
int			ft_strlen_gnl(char *str);
char		*ft_unsigned_itoa(unsigned int i);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_strlcpymod(char *dst, char *src, size_t size);
void		ft_perror(char *error);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
