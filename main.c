/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/08/31 15:44:06 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/mini_rt.h"

void ft_test_parsing(t_window *w)
{
	t_gameobject *test;
	test = malloc(sizeof(t_gameobject));
	test = (t_gameobject *)&w->scene->next->content;
	t_lantern *lights;
	lights = malloc(sizeof(t_lantern));
	lights = (t_lantern *)&(w->lights->next->content);
	printf("A amb %f , %f ,%f \n", w->ambient.color.x, w->ambient.color.y, w->ambient.color.z);
	printf("L pos %f , %f ,%f \n", lights->pos.x, lights->pos.y, lights->pos.z);
	printf("pos cam %f , %f ,%f \n", w->cam.pos.x, w->cam.pos.y, w->cam.pos.z);
	printf("look cam e fov %f , %f ,%f, fov : %f \n", w->cam.lookat.x, w->cam.lookat.y, w->cam.lookat.z, w->cam.fov);
	printf("plane pos %f , %f ,%f \n", test->transform.position.x, test->transform.position.y, test->transform.position.z);
}


int main(int argn, char *args[])
{
	t_window	w;
	
	if (!(argn == 2 || argn == 4))
		ft_print_error(NOARGS, &w);
	else if (argn == 4 && (ft_char_digit(args[2]) || ft_char_digit(args[3])))
		ft_print_error(NOSIZE, &w);
	if (initw(&w, argn, args))
		ft_print_error(NOINIT, &w);
	ft_open_rt(&w, args);
	ft_test_parsing(&w);
	rft_cast(&w, NULL, 0);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "mini_rt");
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
