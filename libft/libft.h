/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:38:37 by iragusa           #+#    #+#             */
/*   Updated: 2022/10/17 18:45:26 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdarg.h>

/*printf struct*/

typedef struct s_flags
{
	int		meno;
	int		zero;
	int		punto;
	int		sign;
	int		canc;
	int		wdt;
	int		prec;
	int		sp;
	int		len;
	int		ret;
	va_list	next;
}	t_flags;

/*list_struct*/

typedef struct s_list
{	
	void			*content;
	struct s_list	*next;
}t_list;

/*libft*/

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_strnum(char *ptr, int n);
int			ft_findchar(char c, char *set);
int			ft_lstsize(t_list *lst);
int			ft_lstsize(t_list *lst);
size_t		ft_strlen(const char *str);
void		*ft_memset(void *p_s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, unsigned int size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_itoa(int n);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstadd_front(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_putstr(char *str);
void		ft_putnstr_fd(char *s, int n, int fd);
char		*ft_dectohex_upper(unsigned long num);
char		*ft_dectohex_low(unsigned long num);
int			ft_dectohex_len(unsigned long num);
char		*ft_strrev(char *str, int j);
char		*get_next_line(int fd);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_read(int fd, char *ret);
char		*ft_line(char *ret);
char		*ft_next_ret(char *ret);
int			checkset(char *str, char *set);

/*ftprintf*/	
t_flags		*ft_inizializza_flag(t_flags *flag);
int			ft_printf(const char *src, ...);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
char		*ft_struint(char *ptr, unsigned long u);
//len
size_t		ft_ptr_len(unsigned long ptr, t_flags *flag);
size_t		ft_uintlen(unsigned int u);
size_t		ft_numlen(int d);
size_t		ft_hexlen(unsigned long x);
//Prints
void		ft_put_c(int c, t_flags *flag);
void		ft_put_s(char *s, t_flags *flag);
void		ft_put_p(unsigned long p, t_flags *flag);
void		ft_intflag(int d, t_flags *flag);
void		ft_uint_flag(t_flags *flag);
void		ft_putint(int n, t_flags *flag);
void		ft_put_di(int n, t_flags *flag);
void		ft_put_u(unsigned long u, t_flags *flag);
void		ft_put_upx(unsigned int x, t_flags *flag);
void		ft_put_lowx(unsigned int x, t_flags *flag);
void		ft_print_lowhex(unsigned long x, t_flags *flag);
void		ft_print_uphex(unsigned long x, t_flags *flag);
void		ft_print_flag(t_flags *flag);
void		ft_printprec(t_flags *flag);
void		ft_print_space(t_flags *flag);
void		ft_print_zero(t_flags *flag);
void		ft_print_space2(t_flags *flag);
void		ft_putchar(char c);
const char	*ft_checkchar(t_flags *flag, const char *src);
const char	*ft_isflag(t_flags *flag, const char *src);
const char	*ft_wdt(t_flags *flag, const char *src);
const char	*ft_prec(t_flags *flag, const char *src);
const char	*ft_convchar(t_flags *flag, const char *src);
void		ft_printsrc(const char *src, t_flags *flag);
void		ft_print_num(char *ptr, int n, t_flags *flag);
void		ft_putint_fd(int n, int fd, t_flags *flag);
void		ft_print_sign(int d, t_flags *flag);
void		ft_print_numzero(t_flags *flag);
void		ft_print_space_s(t_flags *flag);
int			free_mat(char **matrix);
int			ft_printf(const char *src, ...);

#endif
