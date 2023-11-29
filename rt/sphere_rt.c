/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_rt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/28 17:22:33 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	sphere_stuff(t_gameobject *s, t_ray *r, t_tracing_mode mode, double x)
{
	r->data.sqr_distance = x * x;
	r->data.hit_pointer = s;
	if (mode == OCCLUSION || mode == REFERENCE)
		return ;
	r->data.hit_point = ray_at(*r, x);
	r->data.point_normal = v3d_normalize(v3d_sum_2(r->data.hit_point,
				v3d_anti(s->transform.position)));
	if (s->metalness > 0 && metal_manager(r, s))
		return ;
	if (s->metalness == -2 && checker_disr_sphere(s->transform.rotation,
			r, s->color))
		return ;
	if (s->metalness == -1)
		r->data.color = skybox_calc(r->data.point_normal,
				s->texture, &s->transform.rotation);
	else
		r->data.color = s->color;
}

int	hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	oc;
	t_vec3_d	vars;
	double		d;
	t_vec2_d	temp;

	oc = v3d_sum_2(r->source, v3d_anti(sphere->transform.position));
	vars.y = v3d_dot(oc, r->direction);
	vars.z = v3d_sqr_mod(oc) - sphere->transform.scale.x
		* sphere->transform.scale.x;
	d = vars.y * vars.y - vars.z;
	r->data.sqr_distance = INFINITY;
	if (d < 0)
		return (0);
	d = sqrt(d);
	temp.x = -vars.y - d;
	temp.y = -vars.y + d;
	if (temp.x > temp.y)
		temp.x = temp.y;
	if (temp.x < NEGATIVE_LIM)
		return (0);
	sphere_stuff(sphere, r, mode, temp.x);
	return (1);
}
