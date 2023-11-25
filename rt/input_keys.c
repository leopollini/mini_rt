/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2023/11/25 14:56:26 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

static int	keys_manager_4(t_window *win, int keypressed)
{
	if (keypressed == 65429 && win->selected)
		rt_rotate_object(win->selected, aX, win->step);
	else if (keypressed == 65434 && win->selected)
		rt_rotate_object(win->selected, aX, -win->step);
	else if (keypressed == 65436 && win->selected)
		rt_rotate_object(win->selected, aY, win->step);
	else if (keypressed == 65435 && win->selected)
		rt_rotate_object(win->selected, aY, -win->step);
	else if (keypressed == 65439 && win->selected)
		rt_rotate_object(win->selected, aZ, win->step);
	else if (keypressed == 65421 && win->selected)
		rt_rotate_object(win->selected, aZ, -win->step);
	else if (keypressed == 65362)
		win->cam.rotation.x -= win->step / 3;
	else if (keypressed == 65361)
		win->cam.rotation.y -= win->step / 3;
	else if (keypressed == 65364)
		win->cam.rotation.x += win->step / 3;
	else if (keypressed == 65363)
		win->cam.rotation.y += win->step / 3;
	else if (keypressed == 65535 && win->selected)
		win->selected->is_invisible ^= 1;
	else
		return (0);
	return (1);
}

static int	keys_manager_3(t_window *win, int keypressed)
{
	t_transform	*tr;

	tr = &win->selected->transform;
	if (keypressed == 65432)
		tr->position.x += win->step;
	else if (keypressed == 65430)
		tr->position.x -= win->step;
	else if (keypressed == 65431)
		tr->position.y += win->step;
	else if (keypressed == 65433)
		tr->position.y -= win->step;
	else if (keypressed == 65437)
		tr->position.z += win->step;
	else if (keypressed == 65438)
		tr->position.z -= win->step;
	else if (keypressed == 65453)
		tr->scale = v3d_sum_2(tr->scale,
				(t_vec3_d){-win->step, -win->step, -win->step});
	else if (keypressed == 65451)
		tr->scale = v3d_sum_2(tr->scale,
				(t_vec3_d){win->step, win->step, win->step});
	else
		return (0);
	return (1);
}

static int	keys_manager_2(t_window *win, int keypressed)
{
	if (win->selected && keys_manager_3(win, keypressed))
		(void)win;
	else if (keypressed == 65455)
		return (win->step /= SCALE_S, 0);
	else if (keypressed == 65450)
		return (win->step *= SCALE_S, 0);
	else if (keys_manager_4(win, keypressed))
		(void)win;
	else if (keypressed == 32)
		win->selected = NULL;
	else
		return (0);
	if (win->selected)
	{
		if (win->selected->type != SPHERE)
			win->selected->transform.rotation = v3d_normalize(
					win->selected->transform.rotation);
		transform_out(win->selected->transform);
	}
	return (1);
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
	else if (keypressed == 115)
		win->cam.pos.y -= win->step;
	else if (keypressed == 97)
		win->cam.pos.x -= win->step;
	else if (keypressed == 100)
		win->cam.pos.x += win->step;
	else if (keypressed == 101)
		win->cam.pos.z -= win->step;
	else if (keypressed == 114)
		win->cam.pos.z += win->step;
	else
		return (0);
	return (1);
}

int	manage_keys(int keypressed, t_window *win)
{
	printf("[PRESSED: %i]\n", keypressed);
	if (keypressed == 65307 || keypressed == 113)
		win_close(win);
	if (keys_manager_1(win, keypressed))
		(void)win;
	else if (keys_manager_2(win, keypressed))
		(void)win;
	else
		return (0);
	camera_update(win);
	my_image_creator(win);
	return (0);
}
