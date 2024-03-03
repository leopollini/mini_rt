/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:49:05 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 20:53:13 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

char	cyl_collisions_1(t_gameobject *c, t_ray *r, t_vec3_d t)
{
	t_vec3_d	rel_pt;

	rel_pt = v3d_scal(c->trs.rtn, c->trs.scl.y);
	c->trs.pos = v3d_sum_2(c->trs.pos, rel_pt);
	hit_plane((t_plane *)c, r, ALL);
	c->trs.pos = v3d_sub(c->trs.pos, rel_pt);
	if (v3d_sqr_mod(v3d_sub(r->data.hit_point, v3d_sum_2(c->trs.pos,
					rel_pt))) > pow(c->trs.scl.x / 2, 2))
		return (0);
	return (1);
}

char	cyl_collisions(t_gameobject *c, t_ray *r, t_vec3_d t)
{
	t_vec3_d	rel_pt;

	rel_pt = v3d_sub(r->data.hit_point, c->trs.pos);
	if (v3d_dot(rel_pt, c->trs.rtn) < 0)
	{
		c->trs.rtn = v3d_anti(c->trs.rtn);
		hit_plane((t_plane *)c, r, ALL);
		c->trs.rtn = v3d_anti(c->trs.rtn);
		if (v3d_sqr_mod(v3d_sub(r->data.hit_point, c->trs.pos))
			> pow(c->trs.scl.x / 2, 2))
			return (0);
		return (1);
	}
	if (v3d_dot(rel_pt, c->trs.rtn) > c->trs.scl.y)
		return (cyl_collisions_1(c, r, t));
	r->data.hit_point = ray_at(r, t.x);
	r->data.point_normal = cylinder_normal(c->trs, r->data.hit_point);
	r->data.sqr_distance = t.x * t.x;
	return (1);
}

char	cylinder_calcs(t_gameobject *c, t_ray *r, t_vec3_d *t)
{
	t_vec3_d	dt;
	t_vec3_d	c_to_o;
	t_vec3_d	temp;

	r->data.sqr_distance = INFINITY;
	temp = v3d_cross(r->dir, c->trs.rtn);
	c_to_o = v3d_sub(r->source, c->trs.pos);
	dt.x = v3d_dot(temp, temp);
	dt.y = 2 * v3d_dot(temp, v3d_cross(c_to_o, c->trs.rtn));
	dt.z = v3d_dot(v3d_cross(c_to_o, c->trs.rtn),
			v3d_cross(c_to_o, c->trs.rtn))
		- pow(c->trs.scl.x / 2, 2);
	t->z = pow(dt.y, 2) - 4 * dt.z * dt.x;
	if (t->z < 0)
		return (1);
	t->z = sqrt(t->z);
	t->x = (-dt.y - t->z) / (2 * dt.x);
	t->y = t->x + t->z / dt.x;
	if (t->x > t->y)
	{
		t->z = t->x;
		t->x = t->y;
		t->y = t->z;
	}
	return (r->data.hit_point = ray_at(r, t->x), 0);
}

char	cyl_beinside(t_cylinder *c, t_ray *r, t_vec3_d *t, t_tracing_mode mode)
{
	double		a;
	t_vec3_d	s;

	a = v3d_dot(c->trs.rtn, v3d_sub(c->trs.pos, r->source));
	s = v3d_sum_2(c->trs.pos, v3d_scal(c->trs.rtn, a));
	if (v3d_mod(v3d_sub(r->source, s)) > c->trs.scl.y)
		return (0);
	return (1);
}

int	hit_cylinder(t_cylinder *c, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	t;

	if (cylinder_calcs(c, r, &t))
		return (1);
	if (t.x < NEGATIVE_LIM)
		return (0);
	if (!cyl_collisions(c, r, t))
		return (0);
	if (mode == OCCLUSION)
		return (1);
	r->data.hit_ptr = c;
	if (mode == REFERENCE)
		return (1);
	if (c->mtlnss > 0 && metal_manager(r, c))
		return (1);
	r->data.color = c->color;
	return (1);
}
