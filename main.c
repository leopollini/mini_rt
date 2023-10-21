/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/18 16:06:19 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/mini_rt.h"

void	ft_img_obj(t_window *w)
{
	t_list			*ptr;
	t_gameobject	*p;

	if (!w->scene)
		return ;
	ptr = w->scene;
	while (ptr)
	{
		p = (t_gameobject *)ptr->content;
		if (p != NULL && p->text != NULL)
		{
			p->texture.img.img = mlx_xpm_file_to_image(w->mlx, p->text,
					&p->texture.size.x, &p->texture.size.y);
			p->texture.img.addr = mlx_get_data_addr(p->texture.img.img,
					&p->texture.img.bps, &p->texture.img.ll,
					&p->texture.img.en);
			if (p->texture.img.img == NULL || p->texture.img.addr == NULL)
				ft_print_error("error nella texture", w);
		}
		ptr = ptr->next;
	}
}

int	main(int argn, char *args[])
{
	t_window	w;

	if (!(argn == 2 || argn == 3))
		ft_print_error(NOARGS, &w);
	else if (argn == 3 && ft_char_digit(args[2]))
		ft_print_error(NOSIZE, &w);
	w.mlx = mlx_init();
	if (rft_load_scene(&w))
		return (1);
	if (initw(&w))
		ft_print_error(NOINIT, &w);
	ft_open_rt(&w, args);
	rft_cast(&w, NULL, 0);
	ft_img_obj(&w);
	my_image_creator(&w);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	mlx_mouse_hook(w.win, manage_mouse, &w);
	mlx_loop_hook(w.mlx, loop_rt, &w);
	mlx_loop(w.mlx);
}
