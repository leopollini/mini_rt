/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/15 13:54:46 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_raydata	unpack_ray(void *a)
{
	return (*(t_raydata *)a);
}

void	free_obj(t_list *scene)
{
	if (!scene)
		return ;
	if (scene && scene->content)
	{
		if (((t_gameobject *)scene->content)->mtlnss == -1)
			free(((t_gameobject *)scene->content)->text);
		free(scene->content);
	}
	free_obj(scene->next);
	free(scene);
}

t_list	*ft_lstnew_dup(const void *a, int size)
{
	void	*temp;
	int		i;

	i = -1;
	temp = malloc(size);
	while (++i < size)
		((char *)temp)[i] = ((char *)a)[i];
	return (ft_lstnew(temp));
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
