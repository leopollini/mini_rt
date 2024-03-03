/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:03:03 by iragusa           #+#    #+#             */
/*   Updated: 2024/03/02 17:28:54 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

float	tofloat(char **str)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
		w = w * 10 + (*((*str)++) - '0');
	if (**str == '.')
		(*str)++;
	d = 0.0;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	next_val(str);
	return (d * neg);
}

/*color parse and RGB shift*/
t_vec3_d	color_parse(char **str, t_window *w, void *s)
{
	t_vec3_d	pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	pos.x = my_atoi(str);
	if (pos.x < 0 || pos.x > 255)
		ft_print_error("colors R must be in range [0, 255]", w, s);
	ft_comma(str, w, s);
	pos.y = my_atoi(str);
	if (pos.y < 0 || pos.y > 255)
		ft_print_error("colors R must be in range [0, 255]", w, s);
	ft_comma(str, w, s);
	pos.z = my_atoi(str);
	if (pos.z < 0 || pos.z > 255)
		ft_print_error("colors R must be in range [0, 255]", w, s);
	return (pos);
}

t_vec3_d	pos_parse(char **str, t_window *w, void *s)
{
	t_vec3_d	pos;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	next_val(str);
	pos.x = tofloat(str) + E_N2;
	ft_comma(str, w, (t_gameobject *)s);
	pos.y = tofloat(str) + E_N2;
	ft_comma(str, w, (t_gameobject *)s);
	pos.z = tofloat(str) + E_N2;
	return (pos);
}

int	ft_line_parser(t_window *w, char *line)
{
	if (*line == 'R' && *line++)
		return (parse_res(w, &line));
	if (*line == 'A' && *line++)
		return (parse_amb(w, &line));
	if (*line == 'C' && *line++)
		return (parse_cam(w, &line));
	if (*line == 'L' && *line++)
		return (parse_light(w, &line));
	if (ft_strncmp(line, "sp", 2) == 0 && *line++)
		return (parse_sphere(w, &line));
	if (ft_strncmp(line, "pl", 2) == 0 && *line++)
		return (parse_plane(w, &line));
	if (ft_strncmp(line, "cy", 2) == 0 && *line++)
		return (parse_cylinder(w, &line));
	ft_print_error("unexpected identifier in scene file", w, NULL);
	return (0);
}
