/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_rt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 13:24:20 by lpollini         ###   ########.fr       */
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

t_vec3_d	plain_ray_int(t_ray *r, t_transform tr)
{
	double	denom;
	double	t;

	if (v3d_dot(r->direction, tr.rotation) < 0)
	{
		tr.position = v3d_sum_2(tr.position, v3d_scal(tr.rotation, tr.scale.y));
		tr.rotation = v3d_anti(tr.rotation);
	}
	denom = v3d_dot(r->direction, tr.rotation);
	t = v3d_dot(v3d_sum_2(tr.position, v3d_anti(r->source)), tr.rotation) / denom;
	r->data.sqr_distance = t * t;
	return (ray_at(*r, t));
}

int	test_over(t_transform tr, t_vec3_d pt, double dt)
{
	pt = v3d_sum_2(pt, v3d_anti(tr.position));
	if (v3d_dot(pt, tr.rotation) < 0)
		return (-1);
	if (v3d_sqr_mod(pt) > dt)
		return (1);
	return (0);
}

char	parallel_case(t_gameobject *c, t_ray *r)
{
	printf("called. %i\n", 0);
	r->data.sqr_distance = v3d_sqr_mod(v3d_sum_2(c->transform.position, v3d_anti(r->source)));
	return (1);
}

char	cyl_collisions(t_gameobject *c, t_ray *r, t_vec3_d t, char *top)
{
	char	temp;
	char	lol;

	if (t.x != t.x && t.y != t.y)
		return (*top = 1, parallel_case(c, r));
// if (t.x < 0)
// printf("AAAAAAAAAAAAAA");
	if (t.x < POSITIVE_LIM && t.y >= POSITIVE_LIM)
	{
		double_swp(&t.x, &t.y);
		return (cyl_collisions(c, r, t, top));
	}
	if (t.x < POSITIVE_LIM)
		return (0);
	*top = 0;
	r->data.hit_point = ray_at(*r, t.x);
	t.z = pow(c->transform.scale.x / 2, 2) + pow(c->transform.scale.y, 2);
	// if (t.x * t.y < 0)
	// 	printf("called. %i\n", 0);
	temp = test_over(c->transform, r->data.hit_point, t.z);
	if (temp || (t.x * t.y < 0))
	{
		*top = 1;
		t.x = t.y;
		r->data.hit_point = ray_at(*r, t.x);
		t.z = pow(c->transform.scale.x / 2, 2) + pow(c->transform.scale.y, 2);
		lol = test_over(c->transform, r->data.hit_point, t.z);
		if (lol * temp > 0)
			return (0);
		r->data.hit_point = plain_ray_int(r, c->transform);
	}
	else
		r->data.sqr_distance = t.x * t.x;
	if (temp > 0)
		r->data.point_normal = c->transform.rotation;
	else if (temp < 0)
		r->data.point_normal = v3d_anti(c->transform.rotation);
	else
		r->data.point_normal = cylinder_normal(c->transform, r->data.hit_point);
	
	return (1);
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
	//printf("called. %lf # %lf ## %i\n", t->x, t->y, t->x < 0);
	if ((t->x > t->y && t->y > 0))
		double_swp(&t->x, &t->y);
	return (0);
}

int	hit_cylinder(t_cylinder *c, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	t;
	char		top;

	if (cylinder_calcs(c, r, &t))
		return (1);
		//printf("called. %lf\n", t.x);
	if (!cyl_collisions(c, r, t, &top))
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
	r->data.color = c->color;
	return (1);
}
