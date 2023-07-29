/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:56:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/29 09:37:45 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	v3d_out(t_vec3_d a)
{
	printf("called vector out. %f %f %f\n", a.x, a.y, a.z);
}

void	transform_out(t_transform t)
{
	printf("\ncalled transform out.\n----------------------------------------------------\n");
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.position.x, t.position.y, t.position.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.rotation.x, t.rotation.y, t.rotation.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n----------------------------------------------------\n", t.scale.x, t.scale.y, t.scale.z);
}

t_vec2_i	new_v2_i(int x, int y)
{
	return ((t_vec2_i ){x, y});
}

t_vec3_i	new_v3_i(int x, int y, int z)
{
	return ((t_vec3_i ){x, y, z});
}

t_vec2_d	new_v2_d(double x, double y)
{
	return ((t_vec2_d ){x, y});
}

t_vec3_d	new_v3_d(double x, double y, double z)
{
	return ((t_vec3_d ){x, y, z});
}

t_vec3_d	v3_normalize(t_vec3_d in)
{
	double	temp;

	temp = in.x * in.x + in.y * in .y + in.z * in.z;
	if (temp == 1)
		return (in);
	temp = sqrt(temp);
	return ((t_vec3_d ){in.x / temp, in.y / temp, in.z / temp});
}

t_vec3_d	v3d_anti(t_vec3_d a)
{
	return ((t_vec3_d ){-a.x, -a.y, -a.z});
}

t_vec2_d	v2d_anti(t_vec2_d a)
{
	return ((t_vec2_d ){-a.x, -a.y});
}

t_vec3_d	v3_d_scal(t_vec3_d a, double b)
{
	return ((t_vec3_d ){b * a.x, b * a.y, b * a.z});
}

t_vec3_d	ray_at(t_ray r, double t)
{
	return (v3_d_sum(2, r.source, v3_d_scal(v3_normalize(r.direction), t)));
}

double	v3_d_dot(t_vec3_d a, t_vec3_d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	v3_d_sqr_mod(t_vec3_d a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_vec2_d	v2_d_sum(int n, ...)
{
	va_list		args;
	t_vec2_d	res;
	t_vec2_d	temp;

	va_start(args, n);
	res = va_arg(args, t_vec2_d);
	while (--n)
	{
		temp = va_arg(args, const t_vec2_d);
		res.x += temp.x;
		res.y += temp.y;
	}
	va_end(args);
	return (res);
}

t_vec3_d	v3_d_sum_2(t_vec3_d a, t_vec3_d b)
{
	return ((t_vec3_d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3_d	v3_d_sum(int n, ...)
{
	va_list		args;
	t_vec3_d	res;
	t_vec3_d	temp;

	va_start(args, n);
	res = va_arg(args, t_vec3_d);
	while (--n)
	{
		temp = va_arg(args, const t_vec3_d);
		res.x += temp.x;
		res.y += temp.y;
		res.z += temp.z;
	}
	va_end(args);
	return (res);
}

t_vec3_d	v3d_cross(t_vec3_d a, t_vec3_d b)
{
	return ((t_vec3_d){a.y * b.z - a.z * b.y, b.x * a.z - b.z * a.x, a.x * b.y - a.y * b.x});
}

t_vec3_d	color_add(t_vec3_d a, const t_vec3_d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_color_3	color_3_merge(t_color_3 a, t_color_3 b)
{
	return ((t_color_3 ){a.x * b.x / 255, a.y * b.y / 255, a.z * b.z / 255});
}

double	plan_module(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}
