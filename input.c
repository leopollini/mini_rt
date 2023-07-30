/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/30 19:21:50 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	win_close(t_window *win)
{
	win->do_exit = 1;
	rft_window_cast(NULL);
	/*mlx_destroy_image(win->mlx, win->img.img);
	mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	printf("called close window.\n");
	exit(0);*/
}

static int	keys_manager_1(t_window *win, int keypressed)
{
	if (keypressed == 98)
		win->cam.fov *= SCALE_S;
	else if (keypressed == 110)
		win->cam.fov /= SCALE_S;
	else if (keypressed == 122)
		win->anti_aliasing++;
	else if (keypressed == 120 && win->anti_aliasing > 1)
		win->anti_aliasing--;
	else if (keypressed == 104)
		win->toggle_hd = !win->toggle_hd;
	else if (keypressed == 119)
		win->cam.pos.y += win->step;
	else if (keypressed == 97)
		win->cam.pos.y -= win->step;
	else if (keypressed == 115)
		win->cam.pos.x += win->step;
	else if (keypressed == 100)
		win->cam.pos.x -= win->step;
	/*else if (keypressed == 121)
		win->firstp.x -= E_0;
	else if (keypressed == 97)
		win->firstp.y += E_0;*/
	else
		return (0);
	return (1);
}

static int	keys_manager_2(t_window *win, int keypressed)
{
	if (keypressed == 65432 && win->selected)
		win->selected->transform.position.x += win->step;
	else if (keypressed == 65430 && win->selected)
		win->selected->transform.position.x -= win->step;
	else if (keypressed == 65431 && win->selected)
		win->selected->transform.position.y += win->step;
	else if (keypressed == 65433 && win->selected)
		win->selected->transform.position.y -= win->step;
	else if (keypressed == 65437 && win->selected)
		win->selected->transform.position.z += win->step;
	else if (keypressed == 65438 && win->selected)
		win->selected->transform.position.z -= win->step;
	else if (keypressed == 65453 && win->selected)
		win->selected->transform.scale = v3_d_sum_2(win->selected->transform.scale, (t_vec3_d){-win->step, -win->step, -win->step});
	else if (keypressed == 65451 && win->selected)
		win->selected->transform.scale = v3_d_sum_2(win->selected->transform.scale, (t_vec3_d){win->step, win->step, win->step});
	else if (keypressed == 32)
		win->selected = NULL;
	else if (keypressed == 65455)
	{
		win->step /= SCALE_S;
		return (0);
	}
	else if (keypressed == 65450)
	{
		win->step *= SCALE_S;
		return (0);
	}
	else if (keypressed == 65429 && win->selected)
		win->selected->transform.rotation.x += win->step;
	else if (keypressed == 65434 && win->selected)
		win->selected->transform.rotation.x -= win->step;
	else if (keypressed == 65436 && win->selected)
		win->selected->transform.rotation.y += win->step;
	else if (keypressed == 65435 && win->selected)
		win->selected->transform.rotation.y -= win->step;
	else if (keypressed == 65439 && win->selected)
		win->selected->transform.rotation.z += win->step;
	else if (keypressed == 65421 && win->selected)
		win->selected->transform.rotation.z -= win->step;
	else
		return (0);
	if (win->selected)
	{
		win->selected->transform.rotation = v3_normalize(win->selected->transform.rotation);
		transform_out(win->selected->transform);
	}
	return (1);
}

int	manage_keys(int keypressed, t_window *win)
{
	printf("[PRESSED: %i]\n", keypressed);
	if (keypressed == 65307)
		win_close(win);
	if (keys_manager_1(win, keypressed))
		(void)win;
	else if (keys_manager_2(win, keypressed))
		(void)win;
	/*else if (keypressed == 44)
		win->col.z /= SCALE_LL;
	else if (keypressed == 46)
		win->col.z *= SCALE_LL;
	win->iters = MAX_ITER * log(win->col.z / 2 + 25) / 3;*/
	else
		return (0);
	camera_update(win);
	if (!THREADS)
		my_image_creator(win);
	return (0);
}

int	manage_mouse(int button, int x, int y, t_window *w)
{
	t_vec2_i	t;
	t_ray		ray;
	int	a;

	if (button == 5)
		manage_keys(98, w);
	if (button == 4)
		manage_keys(110, w);
	if (button == 1)// || button == 3)
	{
		ray.direction = v3_normalize(new_v3_d((x - w->size.x / 2) * w->cam.scene_window.x / w->size.x, (w->size.y / 2 - y) * w->cam.scene_window.y / w->size.y, w->cam.lookat.z));
		ray.source = w->cam.pos;
		ray.data.hit_pointer = NULL;
		ray.max_sqr_len = INFINITY;
		rft_cast(w, &ray, REFERENCE);
		w->selected = ray.data.hit_pointer;
		if (w->selected)
		{
			printf("called id %i : ", w->selected->defnum);
			transform_out(w->selected->transform);
		}
		else
			printf("called. %s\n", (char *)NULL);
		reimage(w);
	}
	return (0);
}
