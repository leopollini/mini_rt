/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 15:22:59 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/29 11:08:38 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_raydata	unpack_ray(void *a)
{
	return (*(t_raydata *)a);
}

double	double_swp(double *a, double *b)
{
	const double	t = *a;

	*a = *b;
	*b = t;
	return (*a);
}
