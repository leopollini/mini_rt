/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/29 10:48:59 by lpollini         ###   ########.fr       */
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

void	ft_check_path(t_gameobject *s, t_window *w)
{
	FILE	*file;

	file = fopen(s->text, "r");
	if (file == NULL)
	{
		free(s->text);
		ft_print_error("wrong path in the texture", w, (t_gameobject *)s);
	}
	fclose(file);
}

void	free_obj(t_list *scene)
{
	if (!scene)
		return ;
	if (scene && scene->content)
	{
		if (((t_gameobject *)scene->content)->metalness == -1)
			free(((t_gameobject *)scene->content)->text);
		free(scene->content);
	}
	free_obj(scene->next);
	free(scene);
}

int	ft_print_error(char *err, t_window *w, void *del)
{
	write(2, "Error\n ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	if (w->rt != NULL)
		free_mat(w->rt);
	ft_lstclear((&w->lights), free);
	free_obj(w->scene);
	if (del != NULL)
		free(del);
	exit (1);
}
