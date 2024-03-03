/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 21:37:18 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_color_3	rft_specular(t_ray *r, t_ray *lr, t_lantern *l)
{
	const t_vec3_d	res = v3d_specular(lr->dir, r->data.point_normal);

	if (r->data.hit_ptr->type == PLANE)
		return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
								v3d_anti(r->dir)), 200)
						/ 5 * l->intensity)), l->color));
	return (color_3_merge((v3d_scal(r->data.color, pow(v3d_dot(res,
							v3d_anti(r->dir)), 50)
					/ 2 * l->intensity)), l->color));
}

t_color_3	rft_diffuse(t_ray *r, t_ray *o, t_lantern *l)
{
	return (color_3_merge((v3d_scal(r->data.color,
					v3d_dot(r->data.point_normal, o->dir) / 2
					* l->intensity)), l->color));
}

t_vec3_d	rft_search_light(t_window *w, t_ray *r)
{
	t_ray		lr;
	t_list		*lant;
	t_vec3_d	temp;
	t_lantern	*l;

	lr.depth = 0;
	temp = v3d_scal(r->data.color, w->ambient.value);
	lant = w->lights;
	lr.source = r->data.hit_point;
	while (lant->content)
	{
		l = (t_lantern *)lant->content;
		lr.max_sqr_len = v3d_sqr_mod(v3d_sub(lr.source, l->pos));
		lr.dir = v3d_normalize(v3d_sub(l->pos, lr.source));
		if (v3d_dot(r->data.point_normal, lr.dir) > 0)
		{
			lr.data.hit_something = 0;
			rft_cast(NULL, &lr, OCCLUSION);
			if (!lr.data.hit_something)
				temp = v3d_sum(3, temp, rft_diffuse(r, &lr, l),
						rft_specular(r, &lr, l));
		}
		lant = lant->next;
	}
	return (v3d_scal(temp, UNI_SCAL_LIGHT));
}
