/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/25 15:41:34 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	skybox_calc(t_ray r, t_texture t, t_vec3_d *offset)
{
	t_vec3_d		d;
	t_vec2_i		on_pg;
	unsigned int	found_col;

	d = r.direction;
	on_pg.x = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * t.size.x;
	on_pg.y = (0.5 - asin(d.y) / (M_PI)) * t.size.y;
	if (offset)
		on_pg.x = (on_pg.x + (int)offset->x) % t.size.x;
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

t_vec3_d	rft_refract(const t_vec3_d uv, const t_vec3_d n, double t)
{
	const double	cos_theta = double_min(v3d_dot(v3d_anti(uv), n), 1.0);
	const t_vec3_d	r_out_perp = v3d_scal(v3d_sum_2(uv,
				v3d_scal(n, cos_theta)), t);
	const t_vec3_d	r_out_parallel = v3d_scal(n,
			-sqrt(double_abs(1.0 - v3d_sqr_mod(r_out_perp))));

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
