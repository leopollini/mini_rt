/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"


char	*ft_copyadd(char *str)
{
	int		len;
	int		i;
	char	*new;

	len = 0;
	while (str[len] != ' ' && str[len] != '\0')
		len++;
	new = (char *) malloc ((len + 1) * sizeof (char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	ft_check_path(char *s, t_window *w)
{
	FILE	*file;

	file = fopen(s, "r");
	if (file == NULL)
		ft_print_error("wrong path in the texture", w);
}

void	free_obj(t_window *w)
{
	t_gameobject	*obj;
	t_list			*tmp;

	while (w->scene != NULL)
	{
		tmp = w->scene;
		obj = (t_gameobject *)w->scene->content;
		if (obj && obj->text != NULL)
		{
			free(obj->text);
			free(obj);
		}
		w->scene = w->scene->next;
		free(tmp);
	}
}

int	ft_print_error(char *err, t_window *w)
{
	write(2, "Error\n ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	if (w->rt != NULL)
		free_mat(w->rt);
	ft_lstclear((&w->lights), free);
	free_obj(w);
	win_close(w);
	return (1);
}
