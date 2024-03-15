/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:35:59 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 22:42:31 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_cam(t_window *w, char *l)
{
	w->cam.fov = 1;
	w->cam.lookat.z = 1;
	camera_update(w);
	w->cam.id = 'C';
	l++;
	bypass_space(&l, w, NULL);
	w->cam.pos = ft_ato3d(&l, w, NULL);
	bypass_space(&l, w, NULL);
	w->cam.lookat = ft_ato3d(&l, w, NULL);
	if (w->cam.lookat.x < -1 || w->cam.lookat.x > 1
		|| w->cam.lookat.y < -1 || w->cam.lookat.y > 1
		|| w->cam.lookat.z < -1 || w->cam.lookat.z > 1)
		ft_print_error(ERR_RANGE, w, NULL);
	w->cam.lookat = v3d_normalize(w->cam.lookat);
	bypass_space(&l, w, NULL);
	w->cam.fov = pow(ft_atod_shift(&l) / (double )70, 2);
	if (w->cam.fov < 0 || w->cam.fov > 180)
		ft_print_error(ERR_RANGE, w, NULL);
	w->cam.scene_window = new_v2d(w->cam.fov, w->cam.fov);
	w->cam.rtn = ft_get_rot(w->cam.lookat);
	if (l[0] != '\0')
		ft_print_error(ERR_FOBJ, w, NULL);
	camera_update(w);
}
