/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/25 15:44:24 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

double	modulus(double a)
{
	if (a > 0)
		return (a - (double)(long long)a);
	return (1 + (a - (double)(long long)a));
}

char	checker_disr_cyl(t_transform tr, t_ray *r)
{
	int			temp;
	t_vec3_d	d;
	char		i;

	i = 1;
	d = r->data.point_normal;
	d = v3d_normalize((t_vec3_d){d.x, 0, d.z});
	temp = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * 500;
	if (temp % 20 >= 10)
		i = -i;
	if (modulus(v3d_dot(tr.rotation, v3d_sum_2(r->data.hit_point,
					v3d_anti(tr.position)))) > 0.5)
		i = -i;
	if (i == 1)
		r->data.color = (t_vec3_d){0, 0, 0};
	else
		r->data.color = (t_vec3_d){255, 255, 255};
	return (1);
}

char	checker_disr_sphere(t_vec3_d offset, t_ray *r)
{
	t_vec3_d	d;
	t_vec2_i	on_pg;
	char		i;

	i = 1;
	d = r->data.point_normal;
	on_pg.x = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * 500;
	on_pg.y = (0.5 - asin(d.y) / (M_PI)) * 250;
	on_pg.x += offset.x / 2;
	if (on_pg.x % 20 >= 10)
		i = -i;
	if (on_pg.y % 20 >= 10)
		i = -i;
	if (i == 1)
		r->data.color = (t_vec3_d){0, 0, 0};
	else
		r->data.color = (t_vec3_d){255, 255, 255};
	return (1);
}

char	checker_cases(double lol, t_vec3_d tempx, t_vec3_d tempy, t_vec3_d pt)
{
	char	i;

	i = 1;
	if (plian_module(lol) < POSITIVE_LIM)
	{
		lol = pt.x / tempy.x;
		if (modulus(lol) > 0.5)
			i = -i;
		if (tempx.y)
			lol = (pt.y - lol * tempy.y) / tempx.y;
		else
			lol = (pt.z - lol * tempy.z) / tempx.z;
		if (modulus(lol) > 0.5)
			i = -i;
	}
	else
	{
		if (modulus((tempx.y * pt.z - tempx.z * pt.y) / lol) > 0.5)
			i = -i;
		if (modulus((pt.y * tempy.z - pt.z * tempy.y) / lol) > 0.5)
			i = -i;
	}
	return (i);
}

int	checker_disr_plane(t_transform tr, t_ray *r, t_vec3_d pt)
{
	t_vec3_d	tempx;
	t_vec3_d	tempy;
	char		i;
	double		lol;

	i = 0;
	if (tr.rotation.y)
		tempx = v3d_normalize((t_vec3_d){0.01,
				-tr.rotation.z / tr.rotation.y, 1});
	else
		tempx = (t_vec3_d){0, 1, 0};
	tempy = v3d_cross(tr.rotation, tempx);
	i = 1;
	pt = v3d_sum_2(pt, v3d_anti(tr.position));
	lol = tempx.y * tempy.z - tempx.z * tempy.y;
	i = checker_cases(lol, tempx, tempy, pt);
	if (i == 1)
		r->data.color = (t_vec3_d){0, 0, 0};
	else
		r->data.color = (t_vec3_d){255, 255, 255};
	return (1);
}
