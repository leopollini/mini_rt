/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 19:44:08 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	cylinder_normal(t_transform tr, t_vec3_d pt)
{
	double	t;
	t_ray	temp;

	t = v3d_dot(v3d_sum_2(pt, v3d_anti(tr.position)), tr.rotation);
	temp.source = tr.position;
	temp.direction = tr.rotation;
	return (v3d_normalize(v3d_sum_2(pt, v3d_anti(ray_at(temp, t)))));
}

char	plane_isover(t_transform tr, t_vec3_d pt)
{
	if (v3d_dot(tr.rotation, v3d_sum_2(pt, v3d_anti(tr.position))) < 0)
		return (1);
	if (v3d_dot(tr.rotation, v3d_sum(3, v3d_anti(pt), tr.position,
				v3d_scal(tr.rotation, tr.scale.y))) < 0)
		return (-1);
	return (0);
}

void	plane_where(t_transform tr, t_ray *r, char where)
{
	t_vec3_d	norm;
	double		denom;
	double		t;

	norm = tr.rotation;
	denom = v3d_dot(r->direction, norm);
	if (where)
	{
		r->data.point_normal = tr.rotation;
		r->data.color = (t_vec3_d){0,255,0};
	}
	else
	{
		tr.position = v3d_sum_2(tr.position, v3d_scal(tr.rotation, tr.scale.y));
		r->data.point_normal = v3d_anti(tr.rotation);
		r->data.color = (t_vec3_d){0,0,255};
	}
	t = v3d_dot(v3d_sum_2(tr.position,
				v3d_anti(r->source)), norm) / -denom;
	r->data.hit_point = ray_at(*r, t);
	r->data.sqr_distance = t * t;
}

char	cyl_collisions(t_cylinder *c, t_ray *r, t_vec3_d t, char lol)
{
	char	wh;
	char	wh1;

	if (t.x < POSITIVE_LIM && t.y >= POSITIVE_LIM)
		return (double_swp(&t.x, &t.y), cyl_collisions(c, r, t, -lol));
	if (t.x < POSITIVE_LIM)
		return (0);
	r->data.hit_point = ray_at(*r, t.x);
	wh = plane_isover(c->transform, r->data.hit_point);
	if (!wh && t.y > POSITIVE_LIM)
	{
		r->data.sqr_distance = t.x * t.x;
		r->data.point_normal = cylinder_normal(c->transform, r->data.hit_point);
		r->data.color = c->color;
		return (1);
	}
	t.x = t.y;
	r->data.hit_point = ray_at(*r, t.x);
	wh1 = plane_isover(c->transform, r->data.hit_point);
	if ((!wh1 || wh - wh1))
	{
		printf("called. %i # %i # %i\n", wh, wh1, lol);
		return (plane_where(c->transform, r,
				wh * lol < 0 || (!wh && wh1 > 0)), 1);
	}
	return (0);
}

char	cylinder_calcs(t_gameobject *c, t_ray *r, t_vec3_d *t)
{
	t_vec3_d	delta;
	t_vec3_d	c_to_o;
	t_vec3_d	temp;

	r->data.sqr_distance = INFINITY;
	temp = v3d_cross(r->direction, c->transform.rotation);
	c_to_o = v3d_sum_2(r->source, v3d_anti(c->transform.position));
	delta.x = v3d_dot(temp, temp);
	delta.y = 2 * v3d_dot(temp, v3d_cross(c_to_o, c->transform.rotation));
	delta.z = v3d_dot(v3d_cross(c_to_o, c->transform.rotation),
			v3d_cross(c_to_o, c->transform.rotation))
		- pow(c->transform.scale.x / 2, 2);
	t->z = pow(delta.y, 2) - 4 * delta.z * delta.x;
	if (t->z < 0)
		return (1);
	t->z = sqrt(t->z);
	t->x = (-delta.y - t->z) / (2 * delta.x);
	t->y = (-delta.y + t->z) / (2 * delta.x);
	if ((t->x > t->y && t->y > 0))
		double_swp(&t->x, &t->y);
	return (0);
}

int	hit_cylinder(t_cylinder *c, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	t;
	char		top = 1;

	if (cylinder_calcs(c, r, &t))
		return (1);
	// if (mode == LIGHT)
	// 	r->direction = v3d_anti(r->direction);
	if (!cyl_collisions(c, r, t, -1))
		return (0);
	if (mode == OCCLUSION)
		return (1);
	r->data.hit_pointer = c;
	if (mode == REFERENCE)
		return (1);
	if (c->metalness > 0 && metal_manager(r, c))
		return (1);
	if (c->metalness == -2 && ((!top && checker_disr_cyl(c->transform, r,
					c->color)) || checker_disr_plane(c->transform, r,
				r->data.hit_point, c->color)))
		return (1);
	//r->data.color = c->color;
	return (1);
}
