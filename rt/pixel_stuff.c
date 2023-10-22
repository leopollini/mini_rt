/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 09:56:15 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/22 12:32:42 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	reimage(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_do_sync(win->mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int cl)
{
	*(unsigned int *)(data->addr + (y * data->ll + x * (data->bps / 8))) = cl;
}

unsigned int	my_mlx_pixel_get(t_data data, int x, int y)
{
	return (*(unsigned int *)(data.addr + (y * data.ll + x * (data.bps / 8))));
}
