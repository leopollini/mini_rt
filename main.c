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
	// w.mlx = mlx_init();
	// w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "mini_rt hahalol");
	// w.skybox.img = mlx_xpm_file_to_image(w.mlx, "skybox/universe.xpm", &w.skybox_size.x, &w.skybox_size.y);
	// w.skybox.addr = mlx_get_data_addr(w.skybox.img, &w.skybox.bps, &w.skybox.ll, &w.skybox.en);
	// w.img.img = mlx_new_image(w.mlx, w.size.x, w.size.y);
	// w.img.addr = mlx_get_data_addr(w.img.img, &w.img.bps, &w.img.ll, &w.img.en);
	// my_image_creator(&w);
	// mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	// mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	// mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	// mlx_mouse_hook(w.win, manage_mouse, &w);
	// mlx_loop_hook(w.mlx, loop_rt, &w);
	// mlx_loop(w.mlx);
}
