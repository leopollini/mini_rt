/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:35:59 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:47:48 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_cam(t_window *w, char *l)
{
/*	t_vec3_d		lookat; (?)
	t_vec2_d		scene_window; (?)
	t_vec2_d		rtn; (?)
	double			fov; (?)
	*/
	w->cam.id = 'C';
	bypass_space(&l, w);
	w->cam.pos = ft_ato3d(&l, w);
	bypass_space(&l, w);
	w->cam.lookat = ft_ato3d(&l, w);
	if (w->cam.lookat.x < -1 || w->cam.lookat.x > 1
		|| w->cam.lookat.y < -1 || w->cam.lookat.y > 1
		|| w->cam.lookat.z < -1 || w->cam.lookat.z > 1)
		ft_print_error(ERR_RANGE, w, NULL);
	bypass_space(&l, w);
	w->cam.fov = ft_atod_shift(&l);
	if (w->cam.fov < 0 || w->cam.fov > 180)
		ft_print_error(ERR_RANGE, w, NULL);
	if (l[0] != '\0')
		ft_print_error(ERR_FOBJ, w, NULL);
}
