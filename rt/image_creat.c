/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 11:46:27 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

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

t_color_3	rft_specular(t_ray *r, t_ray *lr, t_lantern *l)
{
	const t_vec3_d	res = v3d_specular(lr->direction, r->data.point_normal);

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
						rft_specular(r, &lr, l));
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
	return (skybox_calc(r->direction, aw->skybox, NULL));
}
