/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:25:20 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:48:34 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

double	ft_atod_number_shift(char **l)
{
	double	nb;

	nb = 0;
	while (ft_isdigit(**l))
	{
		nb = nb * 10 + **l - '0';
		(*l)++;
	}
	return (nb);
}

double	ft_atod_shift(char **l)
{
	double	nb;
	double	dec;
	int		sign;

	nb = 0;
	dec = 0.0;
	sign = 1;
	if (**l == '-')
		sign = -1;
	if (**l == '-' || **l == '+')
		(*l)++;
	nb = ft_atod_number_shift(l);
	if (**l == '.')
		(*l)++;
	dec = ft_atod_number_shift(l);
	while (dec >= 1)
		dec /= 10;
	return ((nb + dec) * sign);
}

t_vec3_d	ft_ato3d(char **l, t_window *w)
{
	t_vec3_d	pos;

	pos.x = ft_atod_shift(l);
	if (**l != ',')
		ft_print_error(ERR_FPARAM, w, NULL);
	(*l)++;
	pos.y = ft_atod_shift(l);
	if (**l != ',')
		ft_print_error(ERR_FPARAM, w, NULL);
	(*l)++;
	pos.z = ft_atod_shift(l);
	return (pos);
}

// to add free in object
t_vec3_d	ft_rgb_convert(char **l, t_window *w)
{
	t_vec3_d	pos;

	pos = ft_ato3d(l, w);
	if (pos.x < 0 || pos.x > 255
		|| pos.y < 0 || pos.y > 255
		|| pos.z < 0 || pos.z > 255)
		ft_print_error(ERR_COLOR, w, NULL);
	return (pos);
}
