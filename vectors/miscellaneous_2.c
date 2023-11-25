/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:56:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/04 11:10:26 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"

/* ray direction MUST be normalized!!! */

t_vec3_d	color_add(t_vec3_d a, const t_vec3_d b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_color_3	color_3_merge(t_color_3 a, t_color_3 b)
{
	return ((t_color_3){a.x * b.x / 255, a.y * b.y / 255, a.z * b.z / 255});
}

double	plian_module(double a)
{
	if (a < 0)
		return (-a);
	return (a);
}

t_vec2_d	v2d_sum(int n, ...)
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
