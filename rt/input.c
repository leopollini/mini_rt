/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/15 17:10:31 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	rotate_sphere(t_sphere *o, t_axises a, double rot)
{
	printf("called. rotating sphere by %i\n", (int)(rot * 100));
	if (a == aX)
		o->trs.rtn.x = o->trs.rtn.x + (int)(rot * 100);
}

void	rt_rotate_object(t_gameobject *o, t_axises a, double rot)
{
	const double	cf[2] = {cos(rot / ROT_CONST), sin(rot / ROT_CONST)};
	double			*temp1;
	double			*temp2;
	double			temp3;

	if (o->type == SPHERE)
		return (rotate_sphere(o, a, rot));
	if (a == aX)
	{
		temp1 = &o->trs.rtn.y;
		temp2 = &o->trs.rtn.z;
	}
	if (a == aY)
	{
		temp1 = &o->trs.rtn.z;
		temp2 = &o->trs.rtn.x;
	}
	if (a == aZ)
	{
		temp1 = &o->trs.rtn.x;
		temp2 = &o->trs.rtn.y;
	}
	temp3 = *temp1 * cf[0] - *temp2 * cf[1];
	*temp2 = *temp1 * cf[1] + *temp2 * cf[0];
	*temp1 = temp3;
}

int	manage_mouse(int button, int x, int y, t_window *w)
{
	t_ray		ray;

	if (button == 5)
		manage_keys(65455, w);
	if (button == 4)
		manage_keys(65450, w);
	if (button == 1)
	{
		ray.dir = v3d_normalize(new_v3d((x - w->size.x / 2)
					* w->cam.scene_window.x / w->size.x, (w->size.y
						/ 2 - y) * w->cam.scene_window.y / w->size.y, 1));
		v3d_rotate(&ray.dir, aX, w->cam.rtn.x);
		v3d_rotate(&ray.dir, aY, w->cam.rtn.y);
		ray.source = w->cam.pos;
		ray.data.hit_ptr = NULL;
		ray.max_sqr_len = INFINITY;
		ray.depth = 0;
		rft_cast(w, &ray, REFERENCE);
		w->selected = ray.data.hit_ptr;
		if (w->selected)
			transform_out(w->selected->trs);
		reimage(w);
	}
	return (0);
}
