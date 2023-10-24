/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_opers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:56:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/22 12:32:26 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	create_argb_s(double r, double g, double b)
{
	const t_vec3_d	res = {(r * 128 + 128), (g * 128 + 128), (b * 128 + 128)};

	return (res);
}

int	create_trgb_s(double a, double r, double g, double b)
{
	return ((int)(a * 128 + 128) << 24 | (int)(r * 128 + 128) << 16
			| (int)(g * 128 + 128) << 8 | (int)(b * 128 + 128));
}

int	create_trgb(int a, int r, int g, int b)
{
	if (CREAT_GB_SWITCH)
		return ((a & 0xff) << 24 | (r & 0xff) << 16
			| (g & 0xff) << 8 | (b & 0xff));
	return (a << 24 | r << 16 | g << 8 | b);
}

int	pull_argb(t_vec3_d c, int div)
{
	const int	d_d = div * 255;

	if (c.x > d_d)
		c.x = d_d;
	if (c.y > d_d)
		c.y = d_d;
	if (c.z > d_d)
		c.z = d_d;
	return ((int)(c.x / div) << 16 | (int)(c.y / div) << 8 | (int)(c.z / div));
}

t_vec3_d	create_argb(int r, int g, int b)
{
	const t_vec3_d	res = {r, g, b};

	return (res);
}
