/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:47:46 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/14 22:37:46 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	camera_update(t_window *w)
{
	w->cam.scene_window = new_v2d(w->cam.fov, w->cam.fov);
	return (0);
}

int	initw(t_window *win)
{
	win->size.x = IMGSIZE;
	win->size.y = IMGSIZE;
	if (win->size.x <= 0 || win->size.y <= 0)
		return (write(1, "Window size error\n", 8));
	win->anti_aliasing = START_AA_VAL;
	win->toggle_hd = 0;
	win->step = 0.1;
	win->selected = NULL;
	win->do_exit = 0;
	win->win = mlx_new_window(win->mlx, win->size.x, win->size.y,
			"mini_rt lol");
	win->skybox.img.img = mlx_xpm_file_to_image(win->mlx,
			SKYBOX, &win->skybox.size.x, &win->skybox.size.y);
	win->skybox.img.addr = mlx_get_data_addr(win->skybox.img.img,
			&win->skybox.img.bps, &win->skybox.img.ll, &win->skybox.img.en);
	win->img.img = mlx_new_image(win->mlx, win->size.x, win->size.y);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bps,
			&win->img.ll, &win->img.en);
	return (0);
}

int	loop_rt(t_window *w)
{
	usleep(2000);
	reimage(w);
	return (0);
}

t_vec2_d	ft_get_rot(t_vec3_d v)
{
	double		tz;
	double		cosy;
	double		cosx;
	t_vec2_d	res;

	tz = sqrt(v.x * v.x + v.z * v.z);
	cosy = tz * v.z / (v.x * v.x + v.z * v.z);
	cosx = tz / (v.y * v.y + tz * tz);
	if (!(cosx <= 1 && cosx >= -1))
		cosx = 1;
	if (!(cosy <= 1 && cosy >= -1))
		cosy = 1;
	res = (t_vec2_d){acos(cosx), acos(cosy)};
	if (v.y > 0)
		res.x = -res.x;
	if (v.x < 0)
		res.y = -res.y;
	return (res);
}
