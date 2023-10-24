/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/22 12:41:43 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/*trasmormo i tab in spazi e dopo trimmo*/

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
		ft_print_error(ACL_ERR, w);
	return (0);
}

<<<<<<< HEAD
=======
char	*ft_clean_str(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
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
<<<<<<< HEAD
=======

int	ft_print_error(char *err, t_window *w)
{
	write(STDERR_FILENO, "Error\n ", 7);
	ft_putstr_fd(err, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	win_close(NULL);
	return (1);
}
>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
