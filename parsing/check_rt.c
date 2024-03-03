/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:41:43 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 20:45:16 by lpollini         ###   ########.fr       */
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
	if (a != 1 || c != 1 || l < 1)
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

t_gameobject	*ft_get_text(t_gameobject *p, char **line, t_window *w,
		t_gameobject *o)
{
	p->mtlnss = -1;
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
	ft_check_path(p, w);
	return (p);
}

void	lol_checkmetal(t_gameobject *p, t_window *w, t_gameobject *o)
{
	if (p->mtlnss < 0 || p->mtlnss > 1)
		return ((void)ft_print_error("invalid mtlnss", w, o));
}
