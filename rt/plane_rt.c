/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/28 17:28:44 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

char	plane_stuff(t_gameobject *plane, t_ray *r, t_tracing_mode md, double t)
{
	r->data.hit_pointer = plane;
	r->data.sqr_distance = t * t;
	if (md == OCCLUSION || md == REFERENCE)
		return (1);
	r->data.hit_point = ray_at(*r, t);
	if (plane->metalness == -2)
		return (checker_disr_plane(plane->transform, r,
				r->data.hit_point, plane->color));
	if (plane->metalness > 0 && metal_manager(r, plane))
		return (1);
	return (0);
}

int	hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode)
{
	double		denom;
	t_vec3_d	norm;
	double		t;

	if (plian_module(v3d_dot(plane->transform.rotation, v3d_sum_2(r->source,
					v3d_anti(plane->transform.position))) < POSITIVE_LIM))
		return (0);
	norm = plane->transform.rotation;
	if (mode == OCCLUSION)
		norm = v3d_anti(plane->transform.rotation);
	denom = v3d_dot(r->direction, norm);
	r->data.sqr_distance = INFINITY;
	if (denom >= 0 && mode != REFERENCE)
		return (0);
	t = v3d_dot(v3d_sum_2(plane->transform.position,
				v3d_anti(r->source)), norm) / denom;
	if (t < POSITIVE_LIM)
		return (0);
	r->data.point_normal = norm;
	if (plane_stuff(plane, r, mode, t))
		return (1);
	r->data.color = plane->color;
	return (1);
}
