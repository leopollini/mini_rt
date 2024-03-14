/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/14 22:29:01 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	rft_add_gameobject_to_scene(t_window *w,
			t_gameobject *elem, char *texture)
{
	t_texture	*t;

	elem->defnum = w->obj_num;
	if (texture)
	{
		t = &elem->texture;
		t->img.img = mlx_xpm_file_to_image(w->mlx,
				texture, &t->size.x, &t->size.y);
		t->img.addr = mlx_get_data_addr(t->img.img,
				&t->img.bps, &t->img.ll, &t->img.en);
	}
	ft_lstadd_front(&w->scene, ft_lstnew(elem));
	w->obj_num++;
}
