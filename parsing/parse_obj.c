/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/29 11:04:48 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_gameobject	*ft_metal_alb(t_gameobject *p, char **line,
		t_window *w, t_gameobject *o)
{
	p->metalness = 0;
	p->albedo = 0;
	next_val(line);
	while (**line != 0)
	{
		if (**line == 'a')
		{
			(*line) = (*line) + 2;
			p->albedo = tofloat(line);
		}
		else if ((**line) == 'm')
		{
			(*line) = (*line) + 2;
			p->metalness = tofloat(line);
		}
		else if ((**line) == 't')
			return (ft_get_text(p, line, w, o));
		else if (**line != 't' && **line != 'm' && **line != 'a')
		{
			free(p->text);
			ft_print_error("bad formatted parameter in obj", w, o);
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
	s->transform.position = pos_parse(line, w, (t_gameobject *)s);
	next_val(line);
	s->transform.scale.x = tofloat(line);
	if (s->transform.scale.x <= 0)
		ft_print_error("sphere radius must be > 0", w, (t_gameobject *)s);
	s->transform.scale.y = s->transform.scale.x;
	s->transform.scale.z = s->transform.scale.x;
	next_val(line);
	s->color = color_parse(line, w, s);
	s->defnum = w->obj_num++;
	s->transform.rotation = (t_vec3_d){0, 0, 0};
	s->is_invisible = 0;
	s = ft_metal_alb(s, line, w, s);
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
	p->transform.position = pos_parse(line, w, p);
	next_val(line);
	p->transform.rotation = v3d_normalize(pos_parse(line, w, p));
	next_val(line);
	p->color = color_parse(line, w, p);
	p->defnum = w->obj_num++;
	p->is_invisible = 0;
	p = ft_metal_alb(p, line, w, p);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(p, sizeof(t_plane)));
	w->obj_num++;
	free(p);
	return (0);
}

t_cylinder	*parse_cylinder_help(t_window *w, t_cylinder *c, char **line, int i)
{
	(*line)++;
	c->type = CYLINDER;
	next_val(line);
	c->transform.position = pos_parse(line, w, c);
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
		c->transform.rotation = v3d_normalize(pos_parse(line, w, c));
		next_val(line);
	}
	return (c);
}

int	parse_cylinder(t_window *w, char **line)
{
	t_cylinder	*c;
	int			i;

	i = 0;
	c = sux_malloc(sizeof(t_cylinder), w);
	c->text = NULL;
	c = parse_cylinder_help(w, c, line, i);
	c->transform.scale.x = tofloat(line);
	if (c->transform.scale.x <= 0)
		ft_print_error("cylinder radious must be > 0", w, c);
	next_val(line);
	c->transform.scale.y = tofloat(line);
	if (c->transform.scale.y < 0)
		ft_print_error("cylinder high must be >= 0", w, c);
	c->transform.scale.z = 0;
	c->color = color_parse(line, w, c);
	c->defnum = w->obj_num++;
	c->is_invisible = 0;
	c = ft_metal_alb(c, line, w, c);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(c, sizeof(t_cylinder)));
	w->obj_num++;
	free(c);
	return (0);
}
