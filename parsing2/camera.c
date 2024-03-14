/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:35:59 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 19:29:27 by sdel-gra         ###   ########.fr       */
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
	l++;
	bypass_space(&l, w, NULL);
	w->cam.pos = ft_ato3d(&l, w, NULL);
	bypass_space(&l, w, NULL);
	w->cam.lookat = ft_ato3d(&l, w, NULL);
	if (w->cam.lookat.x < -1 || w->cam.lookat.x > 1
		|| w->cam.lookat.y < -1 || w->cam.lookat.y > 1
		|| w->cam.lookat.z < -1 || w->cam.lookat.z > 1)
		ft_print_error(ERR_RANGE, w, NULL);
	bypass_space(&l, w, NULL);
	w->cam.fov = pow(ft_atod_shift(&l) / (double )70, 2);
	
	if (w->cam.fov < 0 || w->cam.fov > 180)
		ft_print_error(ERR_RANGE, w, NULL);
	if (l[0] != '\0')
		ft_print_error(ERR_FOBJ, w, NULL);
}
