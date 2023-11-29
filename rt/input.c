/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 19:32:48 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	rotate_sphere(t_sphere *o, t_axises a, double rot)
{
	printf("called. rotating sphere by %i\n", (int)(rot * 100));
	if (a == aX)
		o->transform.rotation.x = o->transform.rotation.x + (int)(rot * 100);
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
		temp1 = &o->transform.rotation.y;
		temp2 = &o->transform.rotation.z;
	}
	if (a == aY)
	{
		temp1 = &o->transform.rotation.z;
		temp2 = &o->transform.rotation.x;
	}
	if (a == aZ)
	{
		temp1 = &o->transform.rotation.x;
		temp2 = &o->transform.rotation.y;
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
		ray.direction = v3d_normalize(new_v3d((x - w->size.x / 2)
					* w->cam.scene_window.x / w->size.x, (w->size.y
						/ 2 - y) * w->cam.scene_window.y / w->size.y, 1));
		v3d_rotate(&ray.direction, aX, w->cam.rotation.x);
		v3d_rotate(&ray.direction, aY, w->cam.rotation.y);
		ray.source = w->cam.pos;
		ray.data.hit_pointer = NULL;
		ray.max_sqr_len = INFINITY;
		rft_cast(w, &ray, REFERENCE);
		printf("point, normal, distance = %lf.\n", sqrt(ray.data.sqr_distance));
		v3d_out(ray.data.hit_point);
		v3d_out(ray.data.point_normal);
		w->selected = ray.data.hit_pointer;
		if (w->selected)
			transform_out(w->selected->transform);
		else
			ft_printf("called.\n");
		reimage(w);
	}
	return (0);
}
