/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:56:15 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/02 13:16:01 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

// void	v3d_out(t_vec3_d a)
// {
// 	printf("called vector out. %f %f %f\n", a.x, a.y, a.z);
// }

void	transform_out(t_transform t)
{
	printf("called trs out.\n------------- \
			---------------------------------------\n");
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.pos.x, \
			t.pos.y, t.pos.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n", t.rtn.x, \
			t.rtn.y, t.rtn.z);
	printf("x = % 12f, y = % 12f, z = % 12f\n--- \
			-------------------------------------------------\n", \
			t.scl.x, t.scl.y, t.scl.z);
}

t_vec3_d	ray_at(t_ray *r, double t)
{
	return (v3d_sum_2(r->source, v3d_scal(v3d_normalize(r->dir), t)));
}
