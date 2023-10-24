/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/22 14:51:46 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	rft_load_scene(t_window *w)
{
	w->scene = ft_lstnew(NULL);
	w->lights = ft_lstnew(NULL);
	w->obj_num = 0;
	return (0);
}

void	camera_update(t_window *w)
{
	w->cam.scene_window = new_v2d(w->cam.fov, w->cam.fov);
}

void	camera_init(t_window *win)
{
	t_camera	*tp;

	tp = &win->cam;
	tp->fov = 1;
	tp->pos = (t_vec3_d){0, 0, 0};
	tp->lookat = (t_vec3_d){0, 0, 1};
	tp->rotation = (t_vec2_d){0, 0};
	camera_update(win);
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
<<<<<<< HEAD
	rft_load_scene(win);
	win->win = mlx_new_window(win->mlx, win->size.x, win->size.y,
			"mini_rt");
	win->skybox.img.img = mlx_xpm_file_to_image(win->mlx,
			"skybox/universe.xpm", &win->skybox.size.x, &win->skybox.size.y);
	win->skybox.img.addr = mlx_get_data_addr(win->skybox.img.img,
			&win->skybox.img.bps, &win->skybox.img.ll, &win->skybox.img.en);
	win->img.img = mlx_new_image(win->mlx, win->size.x, win->size.y);
	win->img.addr = mlx_get_data_addr(win->img.img,
			&win->img.bps, &win->img.ll, &win->img.en);
=======
	win->win = mlx_new_window(win->mlx, win->size.x, win->size.y,
			"mini_rt lol");
	win->skybox.img.img = mlx_xpm_file_to_image(win->mlx,
			SKYBOX, &win->skybox.size.x, &win->skybox.size.y);
	win->skybox.img.addr = mlx_get_data_addr(win->skybox.img.img,
			&win->skybox.img.bps, &win->skybox.img.ll, &win->skybox.img.en);
	win->img.img = mlx_new_image(win->mlx, win->size.x, win->size.y);
	win->img.addr = mlx_get_data_addr(win->img.img, &win->img.bps,
			&win->img.ll, &win->img.en);
>>>>>>> 96c89d8363d67293422c321c115fa49b465a9042
	return (0);
}

int	loop_rt(t_window *w)
{
	usleep(2000);
	reimage(w);
	return (0);
}
