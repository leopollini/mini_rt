/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/08/03 17:09:14 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

//str to float

int	parse_res(t_window *w, char **line)
{
	next_val(line);
	w->size.x = my_atoi(line);
	next_val(line);
	if (w->size.x < 1 || w->size.x > INFINITY)
		ft_print_error("resolution x out of range!", w);
	w->size.y = my_atoi(line);
	if (w->size.y < 1 || w->size.y > INFINITY)
		ft_print_error("resolution y out of range!", w);
	return (0);
}

int	parse_amb(t_window *w, char **line)
{
	w->ambient.id = 'A';
	next_val(line);
	w->ambient.value = tofloat(line);
	next_val(line);
	if (w->ambient.value < 0 || w->ambient.value > 1)
		ft_print_error("ambient light out of range!", w);
	w->ambient.color = color_parse(line, w);
	return (0);
}

t_vec2_d	ft_get_rot(t_vec3_d v)
{
	double		tz;
	double		cosy;
	double		cosx;
	t_vec2_d	res;

	tz = sqrt(v.x * v.x + v.z * v.z);
	cosy = tz * v.z / (v.x * v.x + v.z * v.z);
	cosx = tz / (v.y * v.y + tz * tz);
	if (!(cosx <= 1 && cosx >= -1))
		cosx = 1;
	if (!(cosy <= 1 && cosy >= -1))
		cosy = 1;
	res = (t_vec2_d){acos(cosx), acos(cosy)};
	if (v.y > 0)
		res.x = -res.x;
	if (v.x < 0)
		res.y = -res.y;
	return (res);
}

int	parse_cam(t_window *w, char **line)
{
	w->cam.fov = 1;
	w->cam.id = 'C';
	w->cam.pos = pos_parse(line, w);
	next_val(line);
	w->cam.lookat.x = tofloat(line);
	if (w->cam.lookat.x < -1 || w->cam.lookat.x > 1)
		ft_print_error("cam orientation x out of range!", w);
	ft_comma(line, w);
	w->cam.lookat.y = tofloat(line);
	if (w->cam.lookat.y < -1 || w->cam.lookat.y > 1)
		ft_print_error("cam orientation y out of range!", w);
	ft_comma(line, w);
	w->cam.lookat.z = tofloat(line);
	if (w->cam.lookat.z < -1 || w->cam.lookat.z > 1)
		ft_print_error("cam orientation z out of range!", w);
	w->cam.lookat = v3d_normalize(w->cam.lookat);
	next_val(line);
	w->cam.fov = pow(my_atoi(line) / (double )70, 2);
	if (w->cam.fov < 0 || w->cam.fov > 180)
		ft_print_error("cam FOV out of range", w);
	w->cam.scene_window = new_v2d(w->cam.fov, w->cam.fov);
	w->cam.rotation = ft_get_rot(w->cam.lookat);
	camera_update(w);
	return (0);
}

int	parse_light(t_window *w, char **line)
{
	t_lantern	*new;

	new = sux_malloc(sizeof(t_lantern), w);
	new->pos = pos_parse(line, w);
	next_val(line);
	new->intensity = tofloat(line);
	if (new->intensity < 0 || new->intensity > 1)
		ft_print_error("light intensity out of range!", w);
	next_val(line);
	new->color = color_parse(line, w);
	ft_lstadd_front(&w->lights, ft_lstnew_dup(new, sizeof(t_lantern)));
	free(new);
	return (0);
}
