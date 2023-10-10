/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/10 17:58:14 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	rft_load_scene(t_window *w)
{
	w->scene = ft_lstnew(NULL);
	w->lights = ft_lstnew(NULL);
	w->obj_num = 0;

	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0.5, 0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){255, 0, 0}, SPHERE, -1.2));
	//rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3d(0.5, -0.5, 10), new_v3d(0, 0, 1), new_v3d(1, 1, 1)), (t_color_3){0, 255, 0}, SPHERE, 0), NULL);
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(-0.5, 0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){0, 0, 255}, SPHERE, 0));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3d(-0.5, -0.5, 10), new_v3d(0, 0, 1), new_v3d(1, 1, 1)), (t_color_3){0, 255, 255}, SPHERE, 0), NULL);
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 0, 11), new_v3_d(0, 0, 1), new_v3_d(2, 2, 2)), (t_color_3){200, 200, 200}, SPHERE, 0.4));
	// //rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 0, 11), new_v3_d(0, 0, 1), new_v3_d(2, 2, 2)), (t_color_3){200, 200, 200}, SPHERE, 0.4));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(-6, 0, 0), v3_normalize(new_v3_d(1, 0, 0)), new_v3_d(1, 1, 1)), (t_color_3){50, 200, 100}, PLANE, 0));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(6, 0, 0), v3_normalize(new_v3_d(-1, 0, 0)), new_v3_d(1, 1, 1)), (t_color_3){200, 100, 50}, PLANE, 0));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -9, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 9, 0), v3_normalize(new_v3_d(0, -1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -4, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0.5));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -9, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));

	// t_lantern const LG[] = {/*{{-10, -2, 0}, {255, 0, 255}, 2}, {{3, 8, 2}, {200, 255, 200}, 2},*/ {{0, 10, 18}, {200, 250, 230}, 2}, {{0, 7, 2}, {255, 255, 255}, 2}};

	// ft_lstadd_front(&w->lights, ft_lstnew_dup(LG, sizeof(t_lantern)));
	// // ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 1, sizeof(t_lantern)));
	// //ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 2, sizeof(t_lantern)));
	// //ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 3, sizeof(t_lantern)));
	
	
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
	rft_load_scene(win);
}

int	initw(t_window *win, int argn, char *args[])
{
	// if (argn > 3)
	// {
	// 	win->size.x = ft_atoi((const char *)args[1]);
	// 	win->size.y = win->size.x;
	// }
	// else
	(void)argn;
	(void)args;
	{
		win->size.x = 500;
		win->size.y = 500;
	}
	if (win->size.x <= 0 || win->size.y <= 0)
		return (write(1, "Window size error\n", 8));
	camera_init(win);
	win->anti_aliasing = START_AA_VAL;
	win->toggle_hd = 0;
	win->step = 0.1;
	win->selected = NULL;
	win->do_exit = 0;
	return (0);
}

int	loop_rt(t_window *w)
{
	usleep(2000);
	reimage(w);
	return (0);
}