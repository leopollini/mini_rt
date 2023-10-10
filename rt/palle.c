/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:21:11 by lpollini          #+#    #+#             */
/*   Updated: 2023/10/06 23:03:14 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	v3d_rotate(t_vec3_d *v, t_axises a, double rot)
{
	const double	cf[2] = {cos(rot / ROT_CONST), sin(rot / ROT_CONST)};
	double	*temp1;
	double	*temp2;
	double	temp3;

	if (a == aX)
	{
		temp1 = &v->y;
		temp2 = &v->z;
	}
	if (a == aY)
	{
		temp1 = &v->z;
		temp2 = &v->x;
	}
	if (a == aZ)
	{
		temp1 = &v->x;
		temp2 = &v->y;
	}
	temp3 = *temp1 * cf[0] - *temp2 * cf[1];
	*temp2 = *temp1 * cf[1] + *temp2 * cf[0];
	*temp1 = temp3;
}

int	rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp, t_ray *r, t_window *w)
{
	int			div;
	int			a;
	int			b;
	t_vec3_d	temp;

	a = 0;
	div = 0;
	temp = (t_vec3_d){0, 0, 0};
	while (a++ < div_temp.z)
	{
		b = 0;
		while (b++ < div_temp.z)
		{
			r->direction = v3d_normalize(new_v3d((c.x + a / div_temp.z) * div_temp.x, (c.y + b / div_temp.z) * div_temp.y, w->cam.lookat.z));
			v3d_rotate(&r->direction, aX, w->cam.rotation.y);
			v3d_rotate(&r->direction, aY, w->cam.rotation.x);
			temp = color_add(temp, rft_cast(w, r, ALL));
		}
		div += b - 1;
	}
	//if (!c.x && !c.y)
	//	printf("div. %i\n", div);
	return (pull_argb(temp, div));
}

// void	*build_pt(t_window *w, int i, int j)
// {
// 	t_thread	*res;

// 	res = malloc(sizeof(t_thread ));
// 	res->i = i;
// 	res->j = j;
// 	res->w = w;
// 	return (res);
// }

// void	*thread_lol(void *a)
// {
// 	const t_thread	t = *(t_thread *)a;
// 	 t_window	*w = t.w;
// 	t_vec3_d	div_temp;
// 	t_ray		ray;
// 	const t_vec2_i	size = (t_vec2_i){w->size.x / THREADSN, w->size.x / THREADSN};

// 	free(a);
// 	ray.source = w->cam.pos;
// 	ray.depth = 0;
// 	ray.max_sqr_len = INFINITY;

// 	while (!w->do_exit)
// 	{
// 		div_temp = (t_vec3_d){w->cam.scene_window.x / w->size.x, w->cam.scene_window.y / w->size.y, 1};
// 		if (w->toggle_hd)
// 			div_temp.z = w->anti_aliasing;
// 		for (int i = 0; i < w->size.x / THREADSN; i++)
// 			for (int j = 0; j < w->size.y / THREADSN; j++)
// 				my_mlx_pixel_put(&w->img, i + t.i * size.x, w->size.y - (j + t.j * size.y) - 2, rft_anti_aliasing((t_vec2_i){i+ t.i * size.x - w->size.x / 2, j + t.j * size.y - w->size.x / 2}, div_temp, &ray, w));
// 		usleep(200000);
// 	}
// 	return (NULL);
// }

// void	init_threads(t_window *w)
// {
// 	static pthread_t	lol[THREADSN][THREADSN];
// 	int					i;
// 	int					j;

// 	if (!THREADS)
// 		return ;
// 	i = -1;
// 	if (w)
// 		while (++i < THREADSN)
// 		{
// 			j = -1;
// 			while (++j < THREADSN)
// 				pthread_create(&lol[i][j], NULL, thread_lol, build_pt(w, i, j));
// 		}
// 	else
// 		while (++i < THREADSN)
// 		{
// 			j = -1;
// 			while (++j < THREADSN)
// 				pthread_join(lol[i][j], NULL);
// 		}
// }

void rft_window_cast(t_window *w)
{
	t_vec3_d div_temp = {w->cam.scene_window.x / w->size.x, w->cam.scene_window.y / w->size.y, 1};
	t_ray	ray;

	ray.source = w->cam.pos;
	ray.max_sqr_len = INFINITY;
	ray.depth = 0;
	if (w->toggle_hd)
		div_temp.z = w->anti_aliasing;
	// for (int i = 0; i < w->size.x; i++)
	// 	for (int j = 0; j < w->size.y; j++)
	// 		my_mlx_pixel_put(&w->img, i, j, rft_anti_aliasing((t_vec2_i){i, j}, div_temp, &ray, w));
	for (int i = -w->size.x / 2; i < w->size.x / 2; i++)
		for (int j = -w->size.y / 2; j < w->size.y / 2; j++)
			my_mlx_pixel_put(&w->img, i + w->size.x / 2, w->size.x / 2 - j - 1, rft_anti_aliasing((t_vec2_i){i, j}, div_temp, &ray, w));
	//																     /| |\ watch out for this '- 1'!!!
}

void my_image_creator(t_window *w)
{
	printf("info. step = %f, fov = %f, %i-%i\n", w->step, w->cam.fov, w->anti_aliasing, w->toggle_hd);
	// if (THREADS)
	// 	init_threads(w);
	// else
	// {
		rft_window_cast(w);
		reimage(w);
	// }
}
