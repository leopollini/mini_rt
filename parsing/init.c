/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/22 12:24:40 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_gameobject	new_object1(t_transform tr, t_color_3 cl, t_objtype type)
{
	t_gameobject	res;

	res.transform = tr;
	res.color = cl;
	res.type = type;
	return (res);
}

<<<<<<< HEAD
t_gameobject	*new_gameobject(t_transform tr, t_color_3 cl,
			t_objtype type, double sh)
=======
t_gameobject	*new_gameobject(t_transform tr,
			t_color_3 cl, t_objtype type, double sh)
>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
{
	t_gameobject	*res;

	res = malloc(sizeof(t_gameobject));
	res->transform = tr;
	res->color = cl;
	res->type = type;
	res->metalness = sh;
	return (res);
}

t_transform	new_transform(t_vec3_d p, t_vec3_d r, t_vec3_d s)
{
	return ((t_transform){p, r, s});
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

void	rft_add_gameobject_to_scene(t_window *w,
<<<<<<< HEAD
		t_gameobject *elem, char *texture)
=======
			t_gameobject *elem, char *texture)
>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
{
	t_texture	*t;

	elem->defnum = w->obj_num;
	if (texture)
	{
		t = &elem->texture;
<<<<<<< HEAD
		t->img.img = mlx_xpm_file_to_image(w->mlx, texture,
				&t->size.x, &t->size.y);
		t->img.addr = mlx_get_data_addr(t->img.img, &t->img.bps,
				&t->img.ll, &t->img.en);
=======
		t->img.img = mlx_xpm_file_to_image(w->mlx,
				texture, &t->size.x, &t->size.y);
		t->img.addr = mlx_get_data_addr(t->img.img,
				&t->img.bps, &t->img.ll, &t->img.en);
>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
	}
	ft_lstadd_front(&w->scene, ft_lstnew(elem));
	w->obj_num++;
}
