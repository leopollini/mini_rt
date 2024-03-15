/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:25:20 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 15:30:39 by sdel-gra         ###   ########.fr       */
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

t_vec3_d	ft_ato3d(char **l, t_window *w, void *data)
{
	t_vec3_d	pos;

	if (!ft_isdigit(**l) && **l != '-' && **l != '+')
		ft_print_error(ERR_FPARAM, w, data);
	pos.x = ft_atod_shift(l);
	if (**l != ',')
		ft_print_error(ERR_FPARAM, w, data);
	(*l)++;
	if (!ft_isdigit(**l) && **l != '-' && **l != '+')
		ft_print_error(ERR_FPARAM, w, data);
	pos.y = ft_atod_shift(l);
	if (**l != ',')
		ft_print_error(ERR_FPARAM, w, data);
	(*l)++;
	if (!ft_isdigit(**l) && **l != '-' && **l != '+')
		ft_print_error(ERR_FPARAM, w, data);
	pos.z = ft_atod_shift(l);
	return (pos);
}

t_vec3_d	ft_rgb_convert(char **l, t_window *w, void *data)
{
	t_vec3_d	rgb;

	rgb = ft_ato3d(l, w, data);
	if (rgb.x < 0 || rgb.x > 255
		|| rgb.y < 0 || rgb.y > 255
		|| rgb.z < 0 || rgb.z > 255)
		ft_print_error(ERR_COLOR, w, data);
	rgb.x = (int)rgb.x;
	rgb.y = (int)rgb.y;
	rgb.z = (int)rgb.z;
	return (rgb);
}

double	ft_metalness_convert(char **l, t_window *w, void *data)
{
	double	mtlnss;

	if (l[0][0] == 0)
		return (0);
	bypass_space(l, w, data);
	if (*l == NULL || **l == 0 || l[0][1] == 0 || **l != 'm' || l[0][1] != ':')
		ft_print_error(ERR_FPARAM, w, data);
	*l += 2;
	if (!ft_isdigit(**l) && **l != '-' && **l != '+')
		ft_print_error(ERR_FPARAM, w, data);
	mtlnss = ft_atod_shift(l);
	if ((mtlnss < 0 || mtlnss > 1) && mtlnss != -2)
		ft_print_error(ERR_METAL, w, data);
	return (mtlnss);
}
