/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:14:44 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/31 10:51:58 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	show_campos(t_camera ct)
{
	printf("called transform out.\n----------------------------------------------------\n");
	printf("x = % 12f, y = % 12f, z = % 12f\n", ct.pos.x, ct.pos.y, ct.pos.z);
	printf("x = % 12f, y = % 12f\n----------------------------------------------------\n", ct.rotation.x, ct.rotation.y);
}

static int	keys_manager_1(t_window *win, int keypressed)
{
	if (keypressed == 98)	// B ~ increase FOV
		win->cam.fov *= SCALE_S;
	else if (keypressed == 110)	// N ~ decrease FOV
		win->cam.fov /= SCALE_S;
	else if (keypressed == 122)	// Z ~ more antialiasing
		win->anti_aliasing++;
	else if (keypressed == 120 && win->anti_aliasing > 1) // X ~ less antialiasing
		win->anti_aliasing--;
	else if (keypressed == 104)	// H ~ toggle antialiasing (dont if potato)
		win->toggle_hd = !win->toggle_hd;
		// move cam section  WASD
	else if (keypressed == 119)
	{
		win->cam.pos.y += win->step;
		show_campos(win->cam);
	}
	else if (keypressed == 115)
	{
		win->cam.pos.y -= win->step;
		show_campos(win->cam);
	}
	else if (keypressed == 97)
	{
		win->cam.pos.x -= win->step;
		show_campos(win->cam);
	}
	else if (keypressed == 100)
	{
		win->cam.pos.x += win->step;
		show_campos(win->cam);
	}
	else if (keypressed == 101)
	{
		win->cam.pos.z -= win->step;
		show_campos(win->cam);
	}
	else if (keypressed == 114)
	{
		win->cam.pos.z += win->step;
		show_campos(win->cam);
	}
		// end move cam section
	else
		return (0);
	return (1);
}

void	rt_rotate_object(t_gameobject *o, t_axises a, double rot)
{
	const double	cf[2] = {cos(rot / ROT_CONST), sin(rot / ROT_CONST)};
	double	*temp1;
	double	*temp2;
	double	temp3;

printf("called. %lf rotating using %lf %lf\n", rot, cf[0], cf[1]);
	if (a == aX)
	{
		temp1 = &o->transform.rotation.y;
		temp2 = &o->transform.rotation.z;
	}
	if (a == aY)
	{
		temp1 = &o->transform.rotation.z;
		temp2 = &o->transform.rotation.x;
	}
	if (a == aZ)
	{
		temp1 = &o->transform.rotation.x;
		temp2 = &o->transform.rotation.y;
	}
	temp3 = *temp1 * cf[0] - *temp2 * cf[1];
	*temp2 = *temp1 * cf[1] + *temp2 * cf[0];
	*temp1 = temp3;
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
		win->selected->transform.scale = v3d_sum_2(win->selected->transform.scale, (t_vec3_d){-win->step, -win->step, -win->step});
	else if (keypressed == 65451 && win->selected)
		win->selected->transform.scale = v3d_sum_2(win->selected->transform.scale, (t_vec3_d){win->step, win->step, win->step});
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
		// rotation section  on numpad 7,9,1,3,0,'.'
	else if (keypressed == 65429 && win->selected)
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
		// end rotation section
		// cam rotation section
	else if (keypressed == 65362)
	{
		win->cam.rotation.x -= win->step / 3;
		show_campos(win->cam);
	}
	else if (keypressed == 65361)
	{
		win->cam.rotation.y -= win->step / 3;
		show_campos(win->cam);
	}
	else if (keypressed == 65364)
	{
		win->cam.rotation.x += win->step / 3;
		show_campos(win->cam);
	}
	else if (keypressed == 65363)
	{
		win->cam.rotation.y += win->step / 3;
		show_campos(win->cam);
	}
		// end cam rotation
	else if (keypressed == 65535 && win->selected)
		win->selected->is_invisible ^= 1;
	else
		return (0);
	if (win->selected)
	{
		win->selected->transform.rotation = v3d_normalize(win->selected->transform.rotation);
		transform_out(win->selected->transform);
	}
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
	t_ray		ray;

	if (button == 5)
		manage_keys(98, w);
	if (button == 4)
		manage_keys(110, w);
	if (button == 1)// || button == 3)
	{
		ray.direction = v3d_normalize(new_v3d((x - w->size.x / 2) * w->cam.scene_window.x / w->size.x, (w->size.y / 2 - y) * w->cam.scene_window.y / w->size.y, 1));
		v3d_rotate(&ray.direction, aX, w->cam.rotation.x);
		v3d_rotate(&ray.direction, aY, w->cam.rotation.y);
		ray.source = w->cam.pos;
		ray.data.hit_pointer = NULL;
		ray.max_sqr_len = INFINITY;
		rft_cast(w, &ray, REFERENCE);
		w->selected = ray.data.hit_pointer;
		if (w->selected)
		{
			ft_printf("called id %i : ", w->selected->defnum);
			transform_out(w->selected->transform);
			if (w->selected->type == CYLINDER)
				v3d_out(ray.data.point_normal);
		}
		else
			ft_printf("called.\n");
		reimage(w);
	}
	return (0);
}
