/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/31 11:32:38 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	skybox_calc(t_ray r, t_texture t)
{
	t_vec3_d		d;
	t_vec2_i		on_pg;
	unsigned int	found_col;

	d = r.direction;
	on_pg.x = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * t.size.x;
	on_pg.y = (0.5 - asin(d.y) / (M_PI)) * t.size.y;
	found_col = my_mlx_pixel_get(t.img, on_pg.x, on_pg.y);
	return (create_argb((found_col >> 16) & 0xff,
			(found_col >> 8) & 0xff, found_col & 0xff));
}

double	double_min(double a, double b)
{
	if (a > b)
	 	return (b);
	return (a);
}

double	double_abs(double a)
{
	if (a > 0)
	 	return (a);
	return (-a);
}

t_vec3_d rft_refract(const t_vec3_d uv, const t_vec3_d n, double etai_over_etat)
{
	const double	cos_theta = double_min(v3d_dot(v3d_anti(uv), n), 1.0);
	const t_vec3_d	r_out_perp =  v3d_scal(v3d_sum_2(uv, v3d_scal(n, cos_theta)), etai_over_etat);
	const t_vec3_d	r_out_parallel = v3d_scal(n, -sqrt(double_abs(1.0 - v3d_sqr_mod(r_out_perp))));

	return (v3d_normalize(v3d_sum_2(r_out_perp, r_out_parallel)));
}

int	metal_manager(t_ray *r, t_gameobject *gm)
{
	t_ray		refl;
	
	if (r->depth > MAX_REF_DEPTH)
		return (r->data.color = gm->color, 1);
	refl.source = r->data.hit_point;
	refl.max_sqr_len = INFINITY;
	refl.direction = v3d_specular(v3d_anti(r->direction),
			r->data.point_normal);
	refl.depth = r->depth + 1;
	r->data.color = v3d_sumponder(gm->color, rft_cast(NULL,
			&refl, ALL), gm->metalness);
	return (1);
}

t_vec3_d	cylinder_normal(t_transform tr, t_vec3_d pt)
{
	double	t;
	t_ray	temp;

	t = v3d_dot(v3d_sum_2(pt, v3d_anti(tr.position)), tr.rotation);
	temp.source = tr.position;
	temp.direction = tr.rotation;
	return (v3d_normalize(v3d_sum_2(pt, v3d_anti(ray_at(temp, t)))));
}

int	test_over(t_vec3_d rot, t_vec3_d dst, double dt, char fg)
{
	static char	outmode;

	// if (fg)
	// {
	// 	if ((v3d_dot(dst, rot) < 0 ^ outmode > dt) || v3d_sqr_mod(dst) > dt)
	// 		return (1);
	// 	else
	// 		return (0);
	// }
	outmode = v3d_sqr_mod(dst);
	if(v3d_dot(dst, rot) < 0 || outmode > dt)
		return (1);
	return (0);
}

int	hit_cylinder(t_cylinder *cylinder, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	delta;
	t_vec3_d	temp;
	t_vec3_d	c_to_o;
	t_vec3_d	t;

	(void) mode;
	r->data.sqr_distance = INFINITY;
	temp = v3d_cross(r->direction, cylinder->transform.rotation);
	c_to_o = v3d_sum_2(r->source, v3d_anti(cylinder->transform.position));
	delta.x = v3d_dot(temp, temp);
	delta.y = 2 * v3d_dot(temp, v3d_cross(c_to_o, cylinder->transform.rotation));
	delta.z = v3d_dot(v3d_cross(c_to_o, cylinder->transform.rotation), v3d_cross(c_to_o, cylinder->transform.rotation)) - pow(cylinder->transform.scale.x / 2, 2);
	t.z = pow(delta.y, 2) - 4 * delta.z * delta.x;
	if (t.z < 0)
		return (0);
	t.z = sqrt(t.z);
	t.x = (-delta.y - t.z) / (2 * delta.x);
	t.y = t.x + t.z / delta.x;
	if (t.x > t.y)
	{
		t.z = t.x;
		t.x = t.y;
		t.y = t.z;
	}
	if (t.x < NEGATIVE_LIM)
		return (0);

	t.z = pow(cylinder->transform.scale.x / 2, 2) + pow(cylinder->transform.scale.y, 2);
	r->data.hit_point = ray_at(*r, t.x);
	r->data.point_normal = cylinder_normal(cylinder->transform, r->data.hit_point);
	if (test_over(cylinder->transform.rotation, v3d_sum_2(r->data.hit_point, v3d_anti(cylinder->transform.position)), t.z, 0))
	{
		t.x = t.y;
		r->data.hit_point = ray_at(*r, t.x);
		r->data.point_normal = v3d_anti(cylinder->transform.rotation);
		if (test_over(cylinder->transform.rotation, v3d_sum_2(r->data.hit_point, v3d_anti(cylinder->transform.position)), t.z, 1))
			return (0);
	}
	if (mode == OCCLUSION)
		return (1);
	r->data.hit_pointer = cylinder;
	r->data.sqr_distance = t.x * t.x;
	if (mode == REFERENCE)
		return (1);
	if (cylinder->metalness > 0 && metal_manager(r, cylinder))
		return (1);
	r->data.color = cylinder->color;
	return (1);
}

int hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d	oc;
	t_vec3_d	vars;
	double		d;
	t_vec2_d	temp;
	t_ray		refl;

	oc = v3d_sum_2(r->source, v3d_anti(sphere->transform.position));
	vars.y = v3d_dot(oc, r->direction);
	vars.z = v3d_sqr_mod(oc) - sphere->transform.scale.x * sphere->transform.scale.x;
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
	r->data.hit_pointer = sphere;
	r->data.sqr_distance = temp.x * temp.x;
	if (mode == OCCLUSION)
		return (1);
	if (mode == REFERENCE)
		return (1);
	r->data.hit_point = ray_at(*r, temp.x);
	r->data.point_normal = v3d_normalize(v3d_sum_2(r->data.hit_point, v3d_anti(sphere->transform.position)));
	if (sphere->metalness > 0 && metal_manager(r, sphere))
		return (1);
	if (sphere->metalness == -1)
	{
		refl = *r;
		refl.direction = r->data.point_normal;
		r->data.color = skybox_calc(refl, sphere->texture);
	}
	else
		r->data.color = sphere->color;
	return (1);
}

int hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode)
{
	double		denom;
	t_vec3_d	norm;
	double		t;
	t_ray		refl;

	if (mode == OCCLUSION)
		norm = v3d_anti(plane->transform.rotation);
	else
		norm = plane->transform.rotation;
	denom = v3d_dot(r->direction, norm);
	if (denom < 0 || mode == REFERENCE)
	{
		t = v3d_dot(v3d_sum_2(plane->transform.position, v3d_anti(r->source)), norm) / denom;
		if (t < POSITIVE_LIM)
			return (0);
		r->data.hit_pointer = plane;
		r->data.sqr_distance = t * t;
		if (mode == OCCLUSION)
			return (1);
		if (mode == REFERENCE)
			return (1);
		r->data.point_normal = norm;
		r->data.hit_point = ray_at(*r, t);
		if (plane->metalness > 0 && metal_manager(r, plane))
			return (1);
		r->data.color = plane->color;
		return (1);
	}
	r->data.sqr_distance = INFINITY;
	return (0);
}

int	type_sorter(t_objtype t, t_gameobject *obj, t_ray *r, t_tracing_mode mode)
{
	if (obj->is_invisible && mode == ALL)
		return (0);
	if (t == SPHERE)
		return (hit_sphere((t_sphere *)obj, r, mode));
	if (t == PLANE)
		return (hit_plane((t_sphere *)obj, r, mode));
	if (t == CYLINDER)
		return (hit_cylinder((t_cylinder *)obj, r, mode));
	return (0);
}

char rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode)
{
	char			did_hit;
	t_ray 			best;
	//int 			i;
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

t_color_3 rft_specular(t_ray *r, t_ray *lr, t_lantern *l, double lambda)
{
	t_vec3_d	res = v3d_specular(lr->direction, r->data.point_normal);
	(void)lambda;
	if (r->data.hit_pointer->type == PLANE)
		return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
			v3d_anti(r->direction)), 200) / 5 * l->intensity)), l->color));
	return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
			v3d_anti(r->direction)), 50) / 2 * l->intensity)), l->color));
}

t_color_3 rft_diffuse(t_ray *r, t_ray *o, t_lantern *l)
{
	return (color_3_merge((v3d_scal(r->data.color,
			v3d_dot(r->data.point_normal, o->direction) / 2
			* l->intensity)), l->color));
}

t_vec3_d rft_search_light(t_window *w, t_ray *r, t_tracing_mode mode)
{
	t_ray		lray;
	t_list		*lant;
	t_vec3_d	temp;
	t_lantern	*l;
	(void)mode;

	temp = v3d_scal(r->data.color, 0.25);
	lant = w->lights;
	lray.source = r->data.hit_point;
	while (lant->content)
	{
		l = (t_lantern *)lant->content;
		lray.max_sqr_len = v3d_sqr_mod(v3d_sum_2(lray.source, v3d_anti(l->pos)));
		lray.direction = v3d_normalize(v3d_sum_2(l->pos, v3d_anti(lray.source)));
		if (v3d_dot(r->data.point_normal, lray.direction) > 0)
		{
			lray.data.hit_something = 0;
			rft_cast(NULL, &lray, OCCLUSION);
			if (!lray.data.hit_something)
				temp = v3d_sum(3, temp, rft_diffuse(r, &lray, l), rft_specular(r, &lray, l, r->data.hit_pointer->albedo));
		}
		lant = lant->next;
	}
	return (v3d_scal(temp, 0.6));
}

t_vec3_d rft_cast(t_window *w, t_ray *r, t_tracing_mode mode)
{
	static t_window	*aw;

	if (!aw)
	{
		aw = w;
		return ((t_vec3_d){});
	}
	if (mode == OCCLUSION || mode == REFERENCE)
	{
		r->data.hit_something = rft_hitter(aw->scene, r, mode);
		return ((t_vec3_d){});
	}
	if (rft_hitter(aw->scene, r, mode))
	{
		if (r->data.ismetal)
			return (r->data.color);
		return (rft_search_light(aw, r, mode));
	}
	return (skybox_calc(*r, aw->skybox));
}
