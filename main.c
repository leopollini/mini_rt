/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/31 16:58:54 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/mini_rt.h"

t_gameobject new_object1(t_transform tr, t_color_3 cl, t_objtype type)	// return NON malloc'd gameobject
{
	t_gameobject	res;

	res.transform = tr;
	res.color = cl;
	res.type = type;
	return (res);
}

t_gameobject	*new_gameobject(t_transform tr, t_color_3 cl, t_objtype type, double sh)	// return malloc'd gameobject
{
	t_gameobject	*res;

	res = malloc(sizeof(t_gameobject));
	res->transform = tr;
	res->color = cl;
	res->type = type;
	res->metalness = sh;
	return (res);
}

t_transform	new_transform(t_vec3_d p, t_vec3_d r, t_vec3_d s)
{
	return ((t_transform){p, r, s});
}

t_list	*ft_lstnew_dup(const void *a, int size)		// duplicates adding to list (a can be stack'd)
{
	void	*temp;
	int		i;

	i = -1;
	temp = malloc(size);
	while (++i < size)
		((char *)temp)[i] = ((char *)a)[i];
	return (ft_lstnew(temp));
}

void	rft_add_gameobject_to_scene(t_window *w, t_gameobject *elem)	// requires elem to be malloc'd
{
	elem->defnum = w->obj_num;
	ft_lstadd_front(&w->scene, ft_lstnew(elem));
	w->obj_num++;
}

int	rft_load_scene(t_window *w)
{
	w->scene = ft_lstnew(NULL);
	w->lights = ft_lstnew(NULL);
	w->obj_num = 0;

	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0.5, 0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){255, 0, 0}, SPHERE, -1.2));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0.5, -0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){0, 255, 0}, SPHERE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(-0.5, 0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){0, 0, 255}, SPHERE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(-0.5, -0.5, 10), new_v3_d(0, 0, 1), new_v3_d(1, 1, 1)), (t_color_3){0, 255, 255}, SPHERE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 0, 11), new_v3_d(0, 0, 1), new_v3_d(2, 2, 2)), (t_color_3){200, 200, 200}, SPHERE, 0.4));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 0, 11), new_v3_d(0, 0, 1), new_v3_d(2, 2, 2)), (t_color_3){200, 200, 200}, SPHERE, 0.4));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(-6, 0, 0), v3_normalize(new_v3_d(1, 0, 0)), new_v3_d(1, 1, 1)), (t_color_3){50, 200, 100}, PLANE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(6, 0, 0), v3_normalize(new_v3_d(-1, 0, 0)), new_v3_d(1, 1, 1)), (t_color_3){200, 100, 50}, PLANE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -9, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, 9, 0), v3_normalize(new_v3_d(0, -1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));
	rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -4, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0.5));
	// rft_add_gameobject_to_scene(w, new_gameobject(new_transform(new_v3_d(0, -9, 0), v3_normalize(new_v3_d(0, 1, 0)), new_v3_d(1, 1, 1)), (t_color_3){255, 255, 255}, PLANE, 0));

	t_lantern const LG[] = {/*{{-10, -2, 0}, {255, 0, 255}, 2}, {{3, 8, 2}, {200, 255, 200}, 2}, */{{0, 10, 18}, {200, 250, 230}, 1}, {{0, 7, 2}, {255, 255, 255}, 1}};

	ft_lstadd_front(&w->lights, ft_lstnew_dup(LG, sizeof(t_lantern)));
	ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 1, sizeof(t_lantern)));
	//ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 2, sizeof(t_lantern)));
	//ft_lstadd_front(&w->lights, ft_lstnew_dup(LG + 3, sizeof(t_lantern)));
	
	rft_cast(w, NULL, 0);
	return (0);
}

void	camera_update(t_window *w)
{
	w->cam.lookat = v3_normalize(new_v3_d(0, 0, w->cam.focal_len));
	w->cam.scene_window = new_v2_d(w->cam.focal_len * w->cam.fov, w->cam.focal_len * w->cam.fov);
}

void	camera_init(t_window *win)
{
	t_camera	*tp;

	tp = &win->cam;
	tp->focal_len = 1;
	tp->fov = 1;
	tp->pos = (t_vec3_d){0, 0, 0};
	tp->lookat = (t_vec3_d){0, 0, 1};
	camera_update(win);
}

int	initw(t_window *win, int argn, char *args[])
{
	if (argn > 2)
		win->size.x = ft_atoi((const char *)args[1]);
	if (argn > 2)
		win->size.y = ft_atoi((const char *)args[2]);
	else
	{
		win->size.x = 500;
		win->size.y = 500;
	}
	if (win->size.x <= 0 || win->size.y <= 0)
		return (write(1, "Window size error\n", 8));
	if (rft_load_scene(win))
		return (1);
	camera_init(win);
	win->anti_aliasing = START_AA_VAL;
	win->toggle_hd = 0;
	win->step = 0.1;
	win->selected = NULL;
	win->do_exit = 0;
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res);
}

int	loop_rt(t_window *w)
{
	usleep(2000);
	reimage(w);
	return (0);
}

int main(int argn, char *args[])
{
	t_window	w;

	if (initw(&w, argn, args))
		return (0);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "mini_rt hahalol");

	w.skybox.img = mlx_xpm_file_to_image(w.mlx, "skybox/universe.xpm", &w.skybox_size.x, &w.skybox_size.y);
	w.skybox.addr = mlx_get_data_addr(w.skybox.img, &w.skybox.bps, &w.skybox.ll, &w.skybox.en);
	
	w.img.img = mlx_new_image(w.mlx, w.size.x, w.size.y);
	w.img.addr = mlx_get_data_addr(w.img.img, &w.img.bps, &w.img.ll, &w.img.en);

	my_image_creator(&w);
	
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	mlx_mouse_hook(w.win, manage_mouse, &w);
	mlx_loop_hook(w.mlx, loop_rt, &w);
	mlx_loop(w.mlx);
}
