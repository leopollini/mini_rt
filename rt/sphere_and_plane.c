/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_and_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:49:05 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 20:54:36 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	sphere_stuff(t_gameobject *s, t_ray *r, t_tracing_mode mode, double x)
{
	r->data.sqr_distance = x * x;
	r->data.hit_ptr = s;
	if (mode == OCCLUSION || mode == REFERENCE)
		return ;
	r->data.hit_point = ray_at(r, x);
	r->data.point_normal = v3d_normalize(v3d_sub(r->data.hit_point,
				s->trs.pos));
	if (s->mtlnss > 0 && metal_manager(r, s))
		return ;
	if (s->mtlnss == -2 && checker_disr_sphere(s->trs.rtn,
			r, s->color))
		return ;
	if (s->mtlnss == -1)
		r->data.color = skybox_calc(*r, s->texture, &s->trs.rtn);
	else
		r->data.color = s->color;
}

int	hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	oc;
	t_vec3_d	vars;
	double		d;
	t_vec2_d	temp;

	oc = v3d_sub(r->source, sphere->trs.pos);
	vars.y = v3d_dot(oc, r->dir);
	vars.z = v3d_sqr_mod(oc) - sphere->trs.scl.x
		* sphere->trs.scl.x;
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

char	plane_stuff(t_gameobject *plane, t_ray *r, t_tracing_mode md, double t)
{
	r->data.hit_ptr = plane;
	r->data.sqr_distance = t * t;
	if (md == OCCLUSION || md == REFERENCE)
		return (1);
	r->data.hit_point = ray_at(r, t);
	if (plane->mtlnss == -2)
		return (checker_disr_plane(plane->trs, r,
				r->data.hit_point, plane->color));
	if (plane->mtlnss > 0 && metal_manager(r, plane))
		return (1);
	return (0);
}

int	hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode)
{
	double		denom;
	t_vec3_d	norm;
	double		t;

	if (plian_module(v3d_dot(plane->trs.rtn, v3d_sub(r->source,
					plane->trs.pos)) < POSITIVE_LIM))
		return (0);
	norm = plane->trs.rtn;
	if (mode == OCCLUSION)
		norm = v3d_anti(plane->trs.rtn);
	denom = v3d_dot(r->dir, norm);
	r->data.sqr_distance = INFINITY;
	if (denom >= 0 && mode != REFERENCE)
		return (0);
	t = v3d_dot(v3d_sub(plane->trs.pos, r->source), norm) / denom;
	if (t < POSITIVE_LIM)
		return (0);
	r->data.point_normal = norm;
	if (plane_stuff(plane, r, mode, t))
		return (1);
	r->data.color = plane->color;
	return (1);
}
