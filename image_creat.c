/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/29 09:56:46 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec3_d skybox_calc(t_ray r, t_window *w)
{
	t_vec3_d d;
	t_vec2_d on_pg;
	unsigned int found_col;

	d = v3_normalize(v3_d_sum_2(r.direction, v3d_anti(r.source)));
	on_pg.x = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * w->skybox_size.x;
	on_pg.y = (0.5 - asin(d.y) / (M_PI)) * w->skybox_size.y;
	found_col = my_mlx_pixel_get(w->skybox, on_pg.x, on_pg.y);
	return (create_argb((found_col >> 16) & 0xff, (found_col >> 8) & 0xff, found_col & 0xff));
}

int hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d oc;
	t_vec3_d vars;
	double d;
	t_vec2_d temp;

	oc = v3_d_sum_2(r->source, v3d_anti(sphere->transform.position));
	vars.x = v3_d_dot(r->direction, r->direction);
	vars.y = v3_d_dot(oc, r->direction);
	vars.z = v3_d_dot(oc, oc) - sphere->transform.scale.x * sphere->transform.scale.x;
	d = vars.y * vars.y - vars.x * vars.z;
	if (d < 0)
	{
		r->data.sqr_distance = INFINITY;
		return (0);
	}
	d = sqrt(d);
	temp.x = -vars.y - d;
	temp.y = -vars.y + d;
	if (temp.x > temp.y)
		temp.x = temp.y;
	if (temp.x < NEGATIVE_LIM)
		return (0);
	if (mode == OCCLUSION)
		return (1);
	temp.x /=  vars.x;
	r->data.sqr_distance = temp.x * temp.x;
	if (mode == REFERENCE)
	{
		r->data.hit_pointer = sphere;
		return (1);
	}
	r->data.hit_point = ray_at(*r, temp.x);
	r->data.point_normal = v3_normalize(v3_d_sum_2(r->data.hit_point, v3d_anti(sphere->transform.position)));
	//r->data.color = create_argb_s(r->data.point_normal.x, r->data.point_normal.y, r->data.point_normal.z);	//normal-proportioned coloration
	r->data.color = sphere->color;
	return (1);
}

int hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode)
{
	double		denom;
	t_vec3_d	temp;
	double		t;

	denom = v3_d_dot(r->direction, plane->transform.rotation);
	if (denom < POSITIVE_LIM)
	{
		t = v3_d_dot(v3_d_sum_2(plane->transform.position, v3d_anti(r->source)), plane->transform.rotation) / denom;
		if (t < POSITIVE_LIM)
			return (0);
		if (mode == OCCLUSION)
			return (1);
		r->data.sqr_distance = t * t;
		if (mode == REFERENCE)
		{
			r->data.hit_pointer = plane;
			return (1);
		}
		r->data.color = plane->color;
		r->data.hit_point = ray_at(*r, t);
		r->data.point_normal = plane->transform.rotation;
		return (1);
	}
	r->data.sqr_distance = INFINITY;
	return (0);
}

int	hit_cylinder(t_cylinder *cylinder, t_ray *r, t_tracing_mode mode)
{
	return (0);
}

int	type_sorter(t_objtype t, t_gameobject *obj, t_ray *r, t_tracing_mode mode)
{
	if (t == SPHERE)
		return (hit_sphere((t_sphere *)obj, r, mode));
	if (t == PLANE)
		return (hit_plane((t_sphere *)obj, r, mode));
	if (t == CYLINDER)
		return (hit_cylinder((t_cylinder *)obj, r, mode));
}

char rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode)
{
	char			did_hit;
	t_ray 			best;
	int 			i;
	t_gameobject	*obj;

	did_hit = 0;
	i = 0;
	best = *r;
	r->data.sqr_distance = INFINITY;
	while (scene->content)
	{
		obj = (t_gameobject *)scene->content;
		if (scene->content && type_sorter(obj->type, obj, &best, mode))
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

t_color_3 rft_specular(t_ray *r, t_ray *o, t_lantern *l)
{
	return (new_v3_d(0, 0, 0));
}

t_color_3 rft_diffuse(t_ray *r, t_ray *o, t_lantern *l)
{
	return (color_3_merge((v3_d_scal(r->data.color, v3_d_dot(r->data.point_normal, o->direction) / 2 * l->intensity)), l->color));
}

t_vec3_d rft_search_light(t_window *w, t_ray *r, t_tracing_mode mode)
{
	t_ray		lray;
	t_list		*lant;
	t_vec3_d	temp;
	t_lantern	*l;

	temp = v3_d_scal(r->data.color, 0.25);
	lant = w->lights;
	lray.source = r->data.hit_point;

	while (lant->content)
	{
		l = (t_lantern *)lant->content;
		lray.direction = v3_normalize(v3_d_sum_2(l->pos, v3d_anti(lray.source)));
		lray.data.hit_something = 0;
		rft_cast(w, &lray, OCCLUSION);
		if (!lray.data.hit_something)
			temp = v3_d_sum(3, temp, rft_diffuse(r, &lray, l), rft_specular(r, &lray, l));
		lant = lant->next;
	}
	return (v3_d_scal(temp, 0.5));
}

t_vec3_d rft_cast(t_window *w, t_ray *r, t_tracing_mode mode)
{
	if (mode == OCCLUSION)
	{
		r->data.hit_something = rft_hitter(w->scene, r, mode);
		return ((t_vec3_d){});
	}
	if (rft_hitter(w->scene, r, mode))
		return (rft_search_light(w, r, mode));
	return (skybox_calc(*r, w));
}

int	rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp, t_ray *r, t_window *w)
{
	int			div;
	int			a;
	int			b;
	t_vec3_d	temp;

	a = 0;
	div = 0;
	temp = (t_vec3_d){0, 0, 0};
	while (a++ < div_temp.z)
	{
		b = 0;
		while (b++ < div_temp.z)
		{
			r->direction = v3_normalize(new_v3_d((c.x + a / div_temp.z) * div_temp.x, (c.y + b / div_temp.z) * div_temp.y, w->cam.lookat.z));
			temp = color_add(temp, rft_cast(w, r, ALL));
		}
		div += b - 1;
	}
	if (!c.x && !c.y)
		printf("called. %i\n", div);
	return (pull_argb(temp, div));
}

void rft_window_cast(t_window *w)
{
	t_vec3_d div_temp = {w->cam.scene_window.x / w->size.x, w->cam.scene_window.x / w->size.x, 0};
	t_ray	ray;

	div_temp.z = 1;
	ray.source = w->cam.pos;
	if (w->toggle_hd)
		div_temp.z = w->anti_aliasing;
	for (int i = -w->size.x / 2; i < w->size.x / 2; i++)
		for (int j = -w->size.y / 2; j < w->size.y / 2; j++)
			my_mlx_pixel_put(&w->img, i + w->size.x / 2, w->size.x / 2 - j - 1, rft_anti_aliasing((t_vec2_i){i, j}, div_temp, &ray, w));
	//																     /| |\ watch out for this - 1!!!!
}

void my_image_creator(t_window *w)
{
	rft_window_cast(w);

	printf("called. %f, %f, %i-%i\n", w->step, w->cam.fov, w->anti_aliasing, w->toggle_hd);
	reimage(w);
}
