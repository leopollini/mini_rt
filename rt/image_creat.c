/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/25 16:23:01 by lpollini         ###   ########.fr       */
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

int	test_over(t_transform tr, t_vec3_d pt, double dt)
{
	pt = v3d_sum_2(pt, v3d_anti(tr.position));
	if (v3d_dot(pt, tr.rotation) < 0)
		return (-1);
	if (v3d_sqr_mod(pt) > dt)
		return (1);
	return (0);
}

t_vec3_d	plain_ray_int(t_ray *r, t_transform tr, char where)
{
	t_vec3_d	origin;
	double		t;

	origin = v3d_sum_2(tr.position, v3d_anti(r->data.hit_point));
	if (where)
		origin = v3d_sum_2(origin, v3d_scal(tr.rotation, tr.scale.y));
	t = v3d_dot(tr.rotation, origin) / v3d_dot(tr.rotation, r->direction);
	return (ray_at(*r, t));
}

char	cyl_collisions(t_gameobject *c, t_ray *r, t_vec3_d t, char *top)
{
	char		temp;

	*top = 0;
	t.z = pow(c->transform.scale.x / 2, 2) + pow(c->transform.scale.y, 2);
	r->data.hit_point = ray_at(*r, t.x);
	r->data.point_normal = cylinder_normal(c->transform, r->data.hit_point);
	r->data.sqr_distance = t.x * t.x;
	temp = test_over(c->transform, r->data.hit_point, t.z);
	if (temp)
	{
		t.x = t.y;
		r->data.hit_point = ray_at(*r, t.x);
		if (temp > 0)
			r->data.point_normal = v3d_anti(c->transform.rotation);
		else
			r->data.point_normal = c->transform.rotation;
		if (test_over(c->transform, r->data.hit_point, t.z) * temp > 0)
			return (0);
		if (temp < 0)
			r->data.hit_point = plain_ray_int(r, c->transform, 0);
		else
			r->data.hit_point = plain_ray_int(r, c->transform, 1);
		*top = 1;
	}
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
	t->y = t->x + t->z / delta.x;
	if (t->x > t->y)
	{
		t->z = t->x;
		t->x = t->y;
		t->y = t->z;
	}
	return (0);
}

int	hit_cylinder(t_cylinder *cylinder, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	t;
	char		top;

	if (cylinder_calcs(cylinder, r, &t))
		return (1);
	if (t.x < NEGATIVE_LIM)
		return (0);
	if (!cyl_collisions(cylinder, r, t, &top))
		return (0);
	if (mode == OCCLUSION)
		return (1);
	r->data.hit_pointer = cylinder;
	if (mode == REFERENCE)
		return (1);
	if (cylinder->metalness > 0 && metal_manager(r, cylinder))
		return (1);
	if (cylinder->metalness == -2 && ((!top
				&& checker_disr_cyl(cylinder->transform, r))
			|| checker_disr_plane(cylinder->transform, r,
				r->data.hit_point)))
		return (1);
	r->data.color = cylinder->color;
	return (1);
}

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
	if (s->metalness == -2 && checker_disr_sphere(s->transform.rotation, r))
		return ;
	if (s->metalness == -1)
		r->data.color = skybox_calc(*r, s->texture, &s->transform.rotation);
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

char	plane_stuff(t_gameobject *plane, t_ray *r, t_tracing_mode md, double t)
{
	r->data.hit_pointer = plane;
	r->data.sqr_distance = t * t;
	if (md == OCCLUSION || md == REFERENCE)
		return (1);
	r->data.hit_point = ray_at(*r, t);
	if (plane->metalness == -2)
		return (checker_disr_plane(plane->transform, r, r->data.hit_point));
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

int	type_sorter(t_objtype t, t_gameobject *obj, t_ray *r, t_tracing_mode mode)
{
	if (obj->is_invisible)
		return (0);
	if (t == SPHERE)
		return (hit_sphere((t_sphere *)obj, r, mode));
	if (t == PLANE)
		return (hit_plane((t_sphere *)obj, r, mode));
	if (t == CYLINDER)
		return (hit_cylinder((t_cylinder *)obj, r, mode));
	return (0);
}

char	rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode)
{
	char			did_hit;
	t_ray			best;
	t_gameobject	*obj;

	did_hit = 0;
	best = *r;
	r->data.sqr_distance = INFINITY;
	while (scene->content)
	{
		best.data.ismetal = 0;
		obj = (t_gameobject *)scene->content;
		if (scene->content && type_sorter(obj->type, obj, &best, mode)
			&& best.data.sqr_distance < r->max_sqr_len)
		{
			if (mode == OCCLUSION)
				return (1);
			did_hit = 1;
			if (best.data.sqr_distance < r->data.sqr_distance)
				*r = best;
		}
		scene = scene->next;
	}
	return (did_hit);
}

t_color_3	rft_specular(t_ray *r, t_ray *lr, t_lantern *l, double lambda)
{
	const t_vec3_d	res = v3d_specular(lr->direction, r->data.point_normal);

	(void)lambda;
	if (r->data.hit_pointer->type == PLANE)
		return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
								v3d_anti(r->direction)), 200)
						/ 5 * l->intensity)), l->color));
	return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
							v3d_anti(r->direction)), 50)
					/ 2 * l->intensity)), l->color));
}

t_color_3	rft_diffuse(t_ray *r, t_ray *o, t_lantern *l)
{
	return (color_3_merge((v3d_scal(r->data.color,
					v3d_dot(r->data.point_normal, o->direction) / 2
					* l->intensity)), l->color));
}

t_vec3_d	rft_search_light(t_window *w, t_ray *r, t_tracing_mode mode)
{
	t_ray		lr;
	t_list		*lant;
	t_vec3_d	temp;
	t_lantern	*l;

	(void)mode;
	temp = v3d_scal(r->data.color, 0.25);
	lant = w->lights;
	lr.source = r->data.hit_point;
	while (lant->content)
	{
		l = (t_lantern *)lant->content;
		lr.max_sqr_len = v3d_sqr_mod(v3d_sum_2(lr.source, v3d_anti(l->pos)));
		lr.direction = v3d_normalize(v3d_sum_2(l->pos, v3d_anti(lr.source)));
		if (v3d_dot(r->data.point_normal, lr.direction) > 0)
		{
			lr.data.hit_something = 0;
			rft_cast(NULL, &lr, OCCLUSION);
			if (!lr.data.hit_something)
				temp = v3d_sum(3, temp, rft_diffuse(r, &lr, l),
						rft_specular(r, &lr, l, r->data.hit_pointer->albedo));
		}
		lant = lant->next;
	}
	return (v3d_scal(temp, 0.6));
}

t_vec3_d	rft_cast(t_window *w, t_ray *r, t_tracing_mode mode)
{
	static t_window	*aw;

	if (!aw)
	{
		aw = w;
		return ((t_vec3_d){0, 0, 0});
	}
	if (mode == OCCLUSION || mode == REFERENCE)
	{
		r->data.hit_something = rft_hitter(aw->scene, r, mode);
		return ((t_vec3_d){0, 0, 0});
	}
	if (rft_hitter(aw->scene, r, mode))
	{
		if (r->data.ismetal)
			return (r->data.color);
		return (rft_search_light(aw, r, mode));
	}
	return (skybox_calc(*r, aw->skybox, NULL));
}
