/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/27 19:18:11 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	*new_object1(t_sceneobject *res, t_vec2_d size)
{
	res->size = size;
	if (res->type == SPHERE)
		res->sqr_rad = size.x;
	return ((void *)res);
}

void	*new_object(t_vec3_d center, t_vec2_d rotation, t_color color, t_objtype type)
{
	t_sceneobject	*res;

	res = malloc(sizeof(t_sceneobject));
	res->obj_cen = center;
	res->obj_rot = rotation;
	res->color = color;
	res->type = type;
	return (res);
}

t_list	*ft_lstnew_dup(const void *a, int size)
{
	void	*temp;
	int		i;

	i = -1;
	temp = malloc(size);
	while (++i < size)
		((char *)temp)[i] = ((char *)a)[i];
	return (ft_lstnew(temp));
}

int	rft_load_scene(t_window *w)
{
	w->scene = ft_lstnew(NULL);
	w->lights = ft_lstnew(NULL);
	w->obj_num = 0;

	static t_sphere const SP[] = {{{0, 2, 9}, 1, {{0, 0, 0}, {0, 0, 0}, 0}}, {{-2, 2, 9}, 1, {{0, 0, 0}, {0, 0, 0}, 0}}, {{1, -2, 4}, 0.2, {{0, 0, 0}, {0, 0, 0}, 0}},
						{{1.4182, 1.4182, 10}, 2, {{0, 0, 0}, {0, 0, 0}, 0}}};
	static t_lantern const LG[] = {{{100, 0 ,0}, {255, 255, 255}, 1}};

	ft_lstadd_front(&w->scene, ft_lstnew_dup(SP, sizeof(t_sphere)));
	ft_lstadd_front(&w->scene, ft_lstnew_dup(SP + 1, sizeof(t_sphere)));
	ft_lstadd_front(&w->scene, ft_lstnew_dup(SP + 2, sizeof(t_sphere)));
	ft_lstadd_front(&w->scene, ft_lstnew_dup(SP + 3, sizeof(t_sphere)));
	ft_lstadd_front(&w->lights, ft_lstnew_dup(LG, sizeof(t_lantern)));
	w->obj_num = 4;

	//win->lights = ft_lstnew(new_object(new_v3_d(1, 1, -1), new_v2_d(0, 0), \
				create_argb(0, 255, 255, 255), LANTERN));
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

int main(int argn, char *args[])
{
	t_window	w;

	if (initw(&w, argn, args))
		return (0);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "mini_rt hahalol");

	w.skybox.img = mlx_xpm_file_to_image(w.mlx, "skybox/universe.xpm", &w.skybox_size.x, &w.skybox_size.y);
	w.skybox.addr = mlx_get_data_addr(w.skybox.img, &w.skybox.bps, &w.skybox.ll, &w.skybox.en);
	
	v3d_out(v3d_cross(new_v3_d(1, 1, 0), new_v3_d(0, 1, 1)));

	w.img.img = mlx_new_image(w.mlx, w.size.x, w.size.y);
	w.img.addr = mlx_get_data_addr(w.img.img, &w.img.bps, &w.img.ll, &w.img.en);
	my_image_creator(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	mlx_mouse_hook(w.win, manage_mouse, &w);
	mlx_loop(w.mlx);
}
