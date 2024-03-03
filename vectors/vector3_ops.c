/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:02:16 by lpollini          #+#    #+#             */
/*   Updated: 2024/01/27 20:01:08 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"

t_vec3_d	v3d_scal(t_vec3_d a, double b)
{
	return ((t_vec3_d){b * a.x, b * a.y, b * a.z});
}

double	v3d_dot(t_vec3_d a, t_vec3_d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3_d	v3d_cross(t_vec3_d a, t_vec3_d b)
{
	return ((t_vec3_d){a.y * b.z - a.z * b.y, b.x * a.z
		- b.z * a.x, a.x * b.y - a.y * b.x});
}

double	v3d_sqr_mod(t_vec3_d a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	v3d_mod(t_vec3_d a)
{
	return (a.x * a.x + a.y * a .y + a.z * a.z);
}
