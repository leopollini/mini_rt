/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_ops_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:02:16 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/21 17:15:41 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"

t_vec3_d	v3d_sumponder(t_vec3_d a, t_vec3_d b, double p)
{
	return ((t_vec3_d){a.x * (1 - p) + b.x * p, a.y * (1 - p) + \
				b.y * p, a.z * (1 - p) + b.z * p});
}

t_vec3_d	v3d_sum_2(t_vec3_d a, t_vec3_d b)
{
	return ((t_vec3_d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3_d	v3d_sum(int n, ...)
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

t_vec3_d	v3d_anti(t_vec3_d a)
{
	return ((t_vec3_d){-a.x, -a.y, -a.z});
}
