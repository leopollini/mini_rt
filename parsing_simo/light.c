/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:08:45 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 14:32:25 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_light(t_window *w, char *l)
{
	t_lantern	*light;

	light = malloc(sizeof(t_lantern));
	if (!light)
		ft_print_error(MALLOC, w, NULL);
	l++;
	bypass_space(&l, w, light);
	light->pos = ft_ato3d(&l, w, light);
	bypass_space(&l, w, light);
	light->intensity = ft_atod_shift(&l);
	if (light->intensity < 0 || light->intensity > 1)
		ft_print_error(ERR_LIGHT, w, light);
	bypass_space(&l, w, light);
	light->color = ft_rgb_convert(&l, w, light);
	ft_lstadd_front(&w->lights, ft_lstnew_dup(light, sizeof(t_lantern)));
	ft_free((void **)&light);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}
