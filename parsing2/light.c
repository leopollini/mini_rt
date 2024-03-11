/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:08:45 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:54:30 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_vec3_d	ft_color_parse(char **l, t_window *w, t_lantern *light)
{
	t_vec3_d	color;

	(void)light;
	color = ft_ato3d(l, w);
	//if (color.x < 0 || color.x > 255 || color.y < 0 || color.y > 255
	//	|| color.z < 0 || color.z > 255)
	//to be continue
	return (color);
}

void	ft_parse_light(t_window *w, char **l)
{
	t_lantern	*light;

	light = malloc(sizeof(t_lantern));
	if (!light)
		ft_print_error(MALLOC, w, NULL);
	bypass_space(l, w);
	light->pos = ft_ato3d(l, w);
	bypass_space(l, w);
	light->intensity = ft_atod_shift(l);
	if (light->intensity < 0 || light->intensity > 1)
		ft_print_error(ERR_LIGHT, w, light);
	bypass_space(l, w);
	light->color =  ft_rgb_convert(l, w);
	//to be continue

}