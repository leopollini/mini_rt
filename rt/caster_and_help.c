/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster_and_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:47:46 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 20:48:45 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	cylinder_normal(t_transform tr, t_vec3_d pt)
{
	double	t;
	t_ray	temp;

	t = v3d_dot(v3d_sub(pt, tr.pos), tr.rtn);
	temp.source = tr.pos;
	temp.dir = tr.rtn;
	return (v3d_normalize(v3d_sub(pt, ray_at(&temp, t))));
}

int	type_sorter(t_objtype t, t_gameobject *obj, t_ray *r, t_tracing_mode mode)
{
	if (obj->is_invisible)
		return (0);
	if (t == CYLINDER)
		return (hit_cylinder((t_cylinder *)obj, r, mode));
	if (t == SPHERE)
		return (hit_sphere((t_sphere *)obj, r, mode));
	if (t == PLANE)
		return (hit_plane((t_sphere *)obj, r, mode));
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
		if (r->data.hit_ptr->mtlnss <= 0)
			return (rft_search_light(aw, r, mode));
		if (r->data.hit_ptr->mtlnss < 1 && (r->data.hit_ptr->mtlnss > -1))
			return (v3d_sumponder(rft_search_light(aw, r, mode),
					r->data.color, r->data.hit_ptr->mtlnss));
		return (r->data.color);
	}
	return (skybox_calc(*r, aw->skybox, NULL));
}
