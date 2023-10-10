/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:08:34 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/10 18:31:33 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/mini_rt.h"

void	ft_test_parsing(t_window *w)
{
	t_gameobject	test;
	t_lantern		*lights;

	test = *(t_gameobject *)w->scene->next->content;
	lights = malloc(sizeof(t_lantern));
	lights = (t_lantern *)&(w->lights->next->content);
	printf("A amb %f , %f ,%f \n", w->ambient.color.x, w->ambient.color.y, w->ambient.color.z);
	printf("L pos %f , %f ,%f \n", lights->pos.x, lights->pos.y, lights->pos.z);
	printf("pos cam %f , %f ,%f \n", w->cam.pos.x, w->cam.pos.y, w->cam.pos.z);
	printf("look cam e fov %f , %f ,%f, fov : %f \n", w->cam.lookat.x, w->cam.lookat.y, w->cam.lookat.z, w->cam.fov);
	printf("plane pos %f , %f ,%f \n", test.transform.position.x, test.transform.position.y, test.transform.position.z);
}

void	ft_img_obj(t_window *w)
{
	t_list			*ptr;
	t_gameobject	*p;

	if (!w->scene)
		return ;
	ptr = w->scene;
	while (ptr)
	{
		p = (t_gameobject *)w->scene->content;
		if (p->text != NULL)
		{
			p->texture.img.img = mlx_xpm_file_to_image(w->mlx, p->text,
					&p->texture.size.x, &p->texture.size.y);
			p->texture.img.addr = mlx_get_data_addr(p->texture.img.img,
					&p->texture.img.bps, &p->texture.img.ll,
					&p->texture.img.en);
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
	//ft_test_parsing(&w);
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
