/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:41:43 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 21:56:50 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/*turns tabs into spaces and then trim trimmo*/
int	contchar(t_window *w)
{
	int	a;
	int	c;
	int	l;
	int	i;

	a = 0;
	c = 0;
	l = 0;
	i = 0;
	while (w->rt[i])
	{
		if (w->rt[i][0] == 'A')
			a++;
		if (w->rt[i][0] == 'C')
			c++;
		if (w->rt[i][0] == 'L')
			l++;
		i++;
	}
	if (a != 1 || c != 1 || !l)
		ft_print_error(ACL_ERR, w, NULL);
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	c;
	char	*str;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}

static void	ft_isok_path(char *s, t_window *w, t_gameobject *p)
{
	int		i;
	int		fd;
	char	temp[9];

	i = 0;
	while (s[i])
		i++;
	if (i < 5 || s[--i] != 'm' || s[--i] != 'p'
		|| s[--i] != 'x' || s[--i] != '.')
		ft_print_error_free("path must be a .xmp map", w, p, p->text);
	fd = open(p->text, O_RDONLY);
	if (fd <= 0)
		ft_print_error_free("no file found at given path", w, p, p->text);
	if (read(fd, temp, 9) < 9 || ft_strncmp(temp, "/* XPM */", 9))
		ft_print_error_free("invalid file header", w, p, p->text);
	close(fd);
	return ;
}

t_gameobject	*ft_get_text(t_gameobject *p, char **line, t_window *w,
		t_gameobject *o)
{
	int	fd;

	p->metalness = -1;
	(*line) = (*line) + 2;
	p->text = ft_copyadd(*line);
	(*line) += ft_strlen(p->text);
	while (**line != 0)
	{
		if (**line != 32 && **line != 9)
		{
			free(p->text);
			ft_print_error("bad formatted parameter", w, o);
		}
		(*line)++;
	}
	ft_isok_path(p->text, w, p);
	return (p);
}
