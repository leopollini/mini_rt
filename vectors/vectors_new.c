/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:56:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/10 15:55:50 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vectors.h"

t_vec2_i	new_v2i(int x, int y)
{
	return ((t_vec2_i ){x, y});
}

t_vec3_i	new_v3i(int x, int y, int z)
{
	return ((t_vec3_i ){x, y, z});
}

t_vec2_d	new_v2d(double x, double y)
{
	return ((t_vec2_d ){x, y});
}

t_vec3_d	new_v3d(double x, double y, double z)
{
	return ((t_vec3_d ){x, y, z});
}
