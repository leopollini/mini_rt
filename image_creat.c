/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:37:06 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/28 00:14:01 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec3_d create_argb_s(double r, double g, double b)
{
	const t_vec3_d res = {(r * 128 + 128), (g * 128 + 128), (b * 128 + 128)};

	return (res);
}

int create_trgb_s(double a, double r, double g, double b)
{
	return ((int)(a * 128 + 128) << 24 | (int)(r * 128 + 128) << 16 | (int)(g * 128 + 128) << 8 | (int)(b * 128 + 128));
}

int create_trgb(int a, int r, int g, int b)
{
	if (CREAT_GB_SWITCH)
		return ((a & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
	return (a << 24 | r << 16 | g << 8 | b);
}

int pull_argb(t_vec3_d c, int div)
{
	return ((int)(c.x / div) << 16 | (int)(c.y / div) << 8 | (int)(c.z / div));
}

t_vec3_d create_argb(int r, int g, int b)
{
	const t_vec3_d res = {r, g, b};

	return (res);
}

void reimage(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_do_sync(win->mlx);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int cl)
{
	char *dst;

	dst = data->addr + (y * data->ll + x * (data->bps / 8)); // hlep
	*(unsigned int *)dst = cl;
}

t_vec3_d skybox_calc(t_ray r, t_window *w)
{
	t_vec3_d d;
	t_vec2_d on_pg;
	unsigned int found_col;

	d = v3_normalize(v3_d_sum(2, r.direction, v3d_anti(r.source)));
	on_pg.x = (0.5 + atan2(d.z, d.x) / (2 * M_PI)) * w->skybox_size.x;
	on_pg.y = (0.5 - asin(d.y) / (M_PI)) * w->skybox_size.y;
	found_col = *(unsigned int *)(w->skybox.addr + ((int)on_pg.y * w->skybox.ll + (int)on_pg.x * (w->skybox.bps / 8)));
	return (create_argb((found_col >> 16) & 0xff, (found_col >> 8) & 0xff, found_col & 0xff));
}

int hit_sphere(const t_gameobject sphere, t_ray *r, t_tracing_mode mode)
{
	t_vec3_d oc;
	t_vec3_d vars;
	double d;
	t_vec2_d temp;

	oc = v3_d_sum(2, r->source, v3d_anti(sphere.transform.position));
	vars.x = v3_d_dot(r->direction, r->direction);
	vars.y = v3_d_dot(oc, r->direction);
	vars.z = v3_d_dot(oc, oc) - sphere.transform.scale.x * sphere.transform.scale.x;
	d = vars.y * vars.y - vars.x * vars.z;
	if (d < 0)
	{
		r->data.sqr_distance = INFINITY;
		return (0);
	}
	if (mode == OCCLUSION)
		return (1);
	d = sqrt(d);
	temp.x = (-vars.y - d) / vars.x;
	temp.y = (-vars.y + d) / vars.x;
	if (temp.x > temp.y)
		temp.x = temp.y;
	r->data.hit_point = ray_at(*r, temp.x);
	r->data.point_normal = v3_normalize(v3_d_sum(2, r->data.hit_point, v3d_anti(sphere.transform.position)));
	r->data.sqr_distance = v3_d_sqr_mod(v3_d_sum(2, r->data.hit_point, v3d_anti(r->source)));
	r->data.color = create_argb_s(r->data.point_normal.x, r->data.point_normal.y, r->data.point_normal.z);
	return (1);
}

char rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode)
{
	char did_hit;
	t_ray best;
	int i;

	did_hit = 0;
	i = 0;
	best = *r;
	r->data.sqr_distance = INFINITY;
	while (scene->content)
	{
		if (scene->content && hit_sphere(*(const t_gameobject *)scene->content, &best, mode))
		{
			if (mode == OCCLUSION)
				return (1);
			did_hit = 1;
			if (best.data.sqr_distance < r->data.sqr_distance)
				*r = best;
		}
		scene = scene->next;
	}
	return (did_hit);
}

t_vec3_d rft_search_light(t_window *w, t_ray *r, t_tracing_mode mode)
{
	t_ray	lray;

	lray.source = r->data.hit_point;
	lray.direction = v3_normalize(v3_d_sum(2, ((t_lantern *)w->lights->content)->pos, v3d_anti(lray.source)));
	lray.data.hit_something = 0;
	rft_cast(w, &lray, OCCLUSION);
	if (lray.data.hit_something)
		return (r->data.color);
	return (new_v3_d(0, 0, 0));
}

t_vec3_d rft_cast(t_window *w, t_ray *r, t_tracing_mode mode)
{
	if (mode == OCCLUSION)
	{
		if (rft_hitter(w->scene, r, mode))
			r->data.hit_something = 1;
		return (r->data.color);
	}
	if (rft_hitter(w->scene, r, mode))
		return (rft_search_light(w, r, mode));
	return (skybox_calc(*r, w));
}

int	rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp, t_ray *r, t_window *w)
{
	int			div = 0;
	int			a = 0;
	int			b;
	t_vec3_d	temp = (t_vec3_d){0, 0, 0};

	while (a++ < div_temp.z)
	{
		b = 0;
		while (b++ < div_temp.z)
		{
			r->direction = v3_normalize(new_v3_d((c.x + a / div_temp.z) * div_temp.x, (c.y + b / div_temp.z) * div_temp.y, w->cam.lookat.z));
			temp = color_add(temp, rft_cast(w, r, ALL));
		}
		div += b - 1;
	}
	if (!c.x && !c.y)
		printf("called. %i\n", div);
	return (pull_argb(temp, div));
}

void rft_window_cast(t_window *w)
{
	t_vec3_d div_temp = {w->cam.scene_window.x / w->size.x, w->cam.scene_window.x / w->size.x, 0};
	t_ray	ray;

	div_temp.z = 1;
	ray.source = w->cam.pos;
	if (w->toggle_hd)
		div_temp.z = w->anti_aliasing;
	for (int i = -w->size.x / 2; i < w->size.x / 2; i++)
		for (int j = -w->size.y / 2; j < w->size.y / 2; j++)
			my_mlx_pixel_put(&w->img, i + w->size.x / 2, w->size.x / 2 - j - 1, rft_anti_aliasing((t_vec2_i){i, j}, div_temp, &ray, w));
	//																     /| |\ watch out for this - 1!!!!
}

void my_image_creator(t_window *w)
{
	rft_window_cast(w);

	printf("called. %f, %i-%i\n", w->cam.fov, w->anti_aliasing, w->toggle_hd);
	reimage(w);
}
