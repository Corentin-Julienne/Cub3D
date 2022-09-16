/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:23:50 by cjulienn          #+#    #+#             */
/*   Updated: 2022/09/16 13:22:03 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h> 

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_parse
{
	va_list		args;
	const char	*format;
	int			rtn;
	int			i;
}				t_parse;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ---------- MAIN LIBFT WITH BONUS ---------- */

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
size_t		ft_intlen_base(unsigned long long num, size_t base);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
char		*ft_itoa(int n);
char		*ft_lltoa(long long n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putlnbr_base(unsigned long nb, char *base);
void		ft_putlnbr_fd(long long n, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
/* bonus */
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **alst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ---------- FT_PRINTF ---------- */

int			ft_printf(const char *format, ...);
void		ft_printer(t_parse *parse_tab);
t_parse		*ft_inialize_data(t_parse *parse_tab, const char *format);
t_parse		*ft_create_parse_tab(const char *format);
void		ft_find_format(t_parse *parse_tab, int index);
void		ft_handle_percent(t_parse *parse_tab);
void		ft_handle_char(t_parse *parse_tab);
void		ft_handle_void_pointer(t_parse *parse_tab);
void		ft_handle_signed_int(t_parse *parse_tab);
void		ft_handle_string(t_parse *parse_tab);
void		ft_handle_unsigned_int(t_parse *parse_tab);
void		ft_handle_hxd_num(t_parse *parse_tab);
void		ft_handle_upper_hxd_num(t_parse *parse_tab);

/* ---------- GET_NEXT_LINE ----------*/

char		*get_next_line(int fd);
char		*ft_strchr_gnl(const char *s, int c);
size_t		ft_strlen_gnl(const char *s);
char		*ft_mallocable(char *patch);

#endif
