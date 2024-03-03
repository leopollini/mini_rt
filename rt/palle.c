/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:21:11 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/02 13:16:01 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	v3d_rotate(t_vec3_d *v, t_axises a, double rot)
{
	const double	cf[2] = {cos(rot), sin(rot)};
	double			*temp1;
	double			*temp2;
	double			temp3;

	if (a == aX)
	{
		temp1 = &v->y;
		temp2 = &v->z;
	}
	if (a == aY)
	{
		temp1 = &v->z;
		temp2 = &v->x;
	}
	if (a == aZ)
	{
		temp1 = &v->x;
		temp2 = &v->y;
	}
	temp3 = *temp1 * cf[0] - *temp2 * cf[1];
	*temp2 = *temp1 * cf[1] + *temp2 * cf[0];
	*temp1 = temp3;
}

int	rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp,
			t_ray *r, t_window *w)
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
			r->dir = v3d_normalize(new_v3d((c.x + a / div_temp.z)
						* div_temp.x, (c.y + b / div_temp.z) * div_temp.y, 1));
			v3d_rotate(&r->dir, aX, w->cam.rtn.x);
			v3d_rotate(&r->dir, aY, w->cam.rtn.y);
			temp = color_add(temp, rft_cast(w, r, ALL));
		}
		div += b - 1;
	}
	return (pull_argb(temp, div));
}

int	fast_test(const t_vec2_i c, const t_vec3_d div_temp,
			t_ray *r, t_window *w)
{
	r->dir = v3d_normalize(new_v3d((c.x / div_temp.z)
				* div_temp.x, (c.y / div_temp.z) * div_temp.y, 1));
	v3d_rotate(&r->dir, aX, w->cam.rtn.x);
	v3d_rotate(&r->dir, aY, w->cam.rtn.y);
	return (pull_argb(rft_cast(w, r, ALL), 1));
}

void	rft_window_cast(t_window *w)
{
	t_vec3_d	div_temp;
	t_ray		ray;
	int			i;
	int			j;
	int			(*f)(const t_vec2_i, const t_vec3_d, t_ray *, t_window *);

	f = fast_test;
	if (w->toggle_hd)
		f = rft_anti_aliasing;
	div_temp = (t_vec3_d){w->cam.scene_window.x / w->size.x,
		w->cam.scene_window.y / w->size.y, 1};
	ray.source = w->cam.pos;
	ray.max_sqr_len = INFINITY;
	ray.depth = 0;
	if (w->toggle_hd)
		div_temp.z = w->anti_aliasing;
	i = -w->size.x / 2;
	while (i < w->size.x / 2)
	{
		j = -w->size.y / 2 - 1;
		while (++j < w->size.y / 2)
			my_mlx_pixel_put(&w->img, i + w->size.x / 2, w->size.x / 2 - j - 1,
				f((t_vec2_i){i, j}, div_temp, &ray, w));
		i++;
	}
}

void	my_image_creator(t_window *w)
{
	printf("info. step = %f, fov = %f, %i-%i\n", w->step,
		w->cam.fov, w->anti_aliasing, w->toggle_hd);
	rft_window_cast(w);
	reimage(w);
}
