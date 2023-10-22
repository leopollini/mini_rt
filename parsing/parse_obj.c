/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/22 14:56:41 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_gameobject	*ft_metal_alb(t_gameobject *p, char **line)
{
	next_val(line);
	p->metalness = 0;
	p->albedo = 0;
	while (**line != 0)
	{
		if (**line == 'a')
		{
			(*line) = (*line) + 2;
			p->albedo = tofloat(line);
		}
		if ((**line) == 'm')
		{
			(*line) = (*line) + 2;
			p->metalness = tofloat(line);
		}
		if ((**line) == 't')
		{
			(*line) = (*line) + 2;
			p->text = ft_strtrim(*line, " ");
			return (p);
		}
		next_val(line);
	}
	return (p);
}

int	parse_sphere(t_window *w, char **line)
{
	t_sphere	*s;

	(*line)++;
	s = sux_malloc(sizeof(t_sphere), w);
	s->text = NULL;
	s->type = SPHERE;
	next_val(line);
	s->transform.position = pos_parse(line, w);
	next_val(line);
	s->transform.scale.x = tofloat(line);
	if (s->transform.scale.x <= 0)
		ft_print_error("sphere diameter must be > 0", w);
	s->transform.scale.y = s->transform.scale.x;
	s->transform.scale.z = s->transform.scale.x;
	next_val(line);
	s->color = color_parse(line, w);
	s = ft_metal_alb(s, line);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(s, sizeof(t_sphere)));
	w->obj_num++;
	free(s);
	return (0);
}

int	parse_plane(t_window *w, char **line)
{
	t_plane	*p;

	(*line)++;
	p = sux_malloc(sizeof(t_plane), w);
	p->text = NULL;
	p->type = PLANE;
	p->transform.scale.x = 0;
	p->transform.scale.y = 0;
	p->transform.scale.z = 0;
	next_val(line);
	p->transform.position = pos_parse(line, w);
	next_val(line);
	p->transform.rotation = v3d_normalize(pos_parse(line, w));
	next_val(line);
	p->color = color_parse(line, w);
	p = ft_metal_alb(p, line);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(p, sizeof(t_plane)));
	w->obj_num++;
	free(p);
	return (0);
}

t_cylinder	*parse_cylinder_help(t_window *w, t_cylinder *p, char **line, int i)
{
	(*line)++;
	p->type = CYLINDER;
	next_val(line);
	p->transform.position = pos_parse(line, w);
	next_val(line);
	while ((*line)[i] != 0 && (*line)[i] != 32 && (*line)[i] != 9)
	{
		if ((*line)[i] == '.')
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i == -1)
	{
		p->transform.rotation = v3d_normalize(pos_parse(line, w));
		next_val(line);
	}
	return (p);
}

int	parse_cylinder(t_window *w, char **line)
{
	t_cylinder	*p;
	int			i;

	i = 0;
	p = sux_malloc(sizeof(t_cylinder), w);
	p->text = NULL;
	p = parse_cylinder_help(w, p, line, i);
	p->transform.scale.x = tofloat(line);
	if (p->transform.scale.x <= 0)
		ft_print_error("cylinder radious must be > 0", w);
	next_val(line);
	p->transform.scale.y = tofloat(line);
	if (p->transform.scale.y < 0)
		ft_print_error("cylinder high must be >= 0", w);
	p->transform.scale.z = 0;
	p->color = color_parse(line, w);
	p = ft_metal_alb(p, line);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(p, sizeof(t_cylinder)));
	w->obj_num++;
	free(p);
	return (0);
}