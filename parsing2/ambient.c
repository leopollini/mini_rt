/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:08:40 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:47:36 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_ambient(t_window *w, char *l)
{
	w->ambient.id = 'A';
	bypass_space(&l, w);
	w->ambient.value = ft_atod_shift(&l);
	if (w->ambient.value < 0 || w->ambient.value > 1)
		ft_print_error(ERR_RANGE, w, NULL);
	bypass_space(&l, w);
	w->ambient.color = ft_rgb_convert(&l, w);
	if (l[0] != '\0')
		ft_print_error(ERR_FOBJ, w, NULL);
}
