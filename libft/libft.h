/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:34:20 by flenski           #+#    #+#             */
/*   Updated: 2026/02/18 13:26:38 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				free_ptr_array(void **arr);
int					ft_atoi(const char *nptr);
int					ft_base_numlen(long num, int blen);
void				ft_bzero(void*str, size_t len);
void				*ft_calloc(size_t amount, size_t size);
char				*convert_base(const char *num_str, const char *input_base,
						const char *output_base);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
char				*ft_itoa(long long n);
char				*itoa_base(int n, const char *base);
void				ft_lstadd_back(t_list **lst, t_list *newNode);
void				ft_lstadd_front(t_list **lst, t_list *newNode);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memchr(const void *p, int c, size_t slen);
int					ft_memcmp(const void *p1, const void *p2, size_t slen);
void				*ft_memcpy(void *dest, const void *src, size_t slen);
void				*ft_memmove(void *dest, const void *src, size_t slen);
void				*ft_memset(void *p, int c, size_t slen);
int					ft_numlen(long long n);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char*str, int fd);
int					ft_putnbr_base_fd(int num, const char *base, int fd);
int					ft_putnbr_fd(long long num, int is_unsigned, int fd);
void				ft_putnbr_fd_rec(int n, int fd);
int					ft_putstr_fd(char*str, int fd);
char				**ft_split(char const*str, char del, int empty_str);
char				*ft_strchr(const char*str, int c);
char				*ft_strdup(const char *s);
void				ft_striteri(char*str, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strmapi(char const*str, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t num);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
size_t				ft_strlen(const char *s);
size_t				ft_strlend(const char *str, int del);
char				*ft_strrchr(const char*str, int c);
char				*ft_strrev(char *str);
long				ft_strtol(const char *str, const char *base, int blen);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const*str, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_unumlen(unsigned long long n);
char				*ft_utoa(unsigned long long n);

#endif