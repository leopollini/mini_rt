/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:56:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/06 19:07:23 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

// void	v3d_out(t_vec3_d a)
// {
// 	printf("called vector out. %f %f %f\n", a.x, a.y, a.z);
// }

void	transform_out(t_transform t)
{
	printf("called transform out.\n----------------------------------------------------\n");
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.position.x, t.position.y, t.position.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.rotation.x, t.rotation.y, t.rotation.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n----------------------------------------------------\n", t.scale.x, t.scale.y, t.scale.z);
}

t_vec3_d	ray_at(t_ray r, double t)
{
	return (v3d_sum_2(r.source, v3d_scal(v3d_normalize(r.direction), t)));
}
