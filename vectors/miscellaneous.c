/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscellaneous.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:02:16 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/21 17:19:09 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"

t_vec2_d	v2d_anti(t_vec2_d a)
{
	return ((t_vec2_d){-a.x, -a.y});
}

t_vec3_d	v3d_specular(t_vec3_d v, t_vec3_d normal)
{
	return (v3d_sum_2(v3d_scal(normal, v3d_dot(v, normal) * 2), v3d_anti(v)));
}

t_vec3_d	v3d_normalize(t_vec3_d in)
{
	double	temp;

	temp = in.x * in.x + in.y * in .y + in.z * in.z;
	if (temp == 1)
		return (in);
	temp = sqrt(temp);
	return ((t_vec3_d){in.x / temp, in.y / temp, in.z / temp});
}

void	v3d_out(t_vec3_d a)
{
	printf("called vector out. %f %f %f\n", a.x, a.y, a.z);
}
