/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:09:12 by iragusa           #+#    #+#             */
/*   Updated: 2024/03/03 22:22:52 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

t_gameobject	*ft_metal_alb(t_gameobject *p, char **line,
		t_window *w, t_gameobject *o)
{
	p->mtlnss = 0;
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
			p->mtlnss = tofloat(line);
		}
		else if ((**line) == 't')
			return (p->mtlnss = -1, ft_get_text(p, line, w, o));
		else if (**line != 't' && **line != 'm' && **line != 'a')
		{
			free(p->text);
			ft_print_error("bad formatted parameter in obj", w, o);
		}
		next_val(line);
	}
	return (lol_checkmetal(p, w, o), p);
}

int	parse_sphere(t_window *w, char **line)
{
	t_sphere	*s;

	(*line)++;
	s = sux_malloc(sizeof(t_sphere), w);
	s->text = NULL;
	s->type = SPHERE;
	next_val(line);
	s->trs.pos = pos_parse(line, w, (t_gameobject *)s);
	next_val(line);
	s->trs.scl.x = tofloat(line) / 2;
	if (s->trs.scl.x <= 0)
		ft_print_error("sphere diameter must be > 0", w, (t_gameobject *)s);
	s->trs.scl.y = s->trs.scl.x;
	s->trs.scl.z = s->trs.scl.x;
	s->trs.rtn = (t_vec3_d){0, 0, 0};
	next_val(line);
	s->color = color_parse(line, w, s);
	s->defnum = w->obj_num++;
	s->trs.rtn = (t_vec3_d){0, 0, 0};
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
	p->trs.scl.x = 0;
	p->trs.scl.y = 0;
	p->trs.scl.z = 0;
	next_val(line);
	p->trs.pos = pos_parse(line, w, p);
	next_val(line);
	p->trs.rtn = v3d_normalize(pos_parse(line, w, p));
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
	c->trs.pos = pos_parse(line, w, c);
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
		c->trs.rtn = v3d_normalize(pos_parse(line, w, c));
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
	c->trs.scl.y = INFINITY;
	c->text = NULL;
	c = parse_cylinder_help(w, c, line, i);
	c->trs.scl.x = tofloat(line);
	if (c->trs.scl.x <= 0)
		ft_print_error("cylinder diameter must be > 0", w, c);
	next_val(line);
	c->trs.scl.y = tofloat(line);
	if (c->trs.scl.y < 0)
		ft_print_error("cylinder high must be >= 0", w, c);
	c->trs.scl.z = 0;
	c->color = color_parse(line, w, c);
	c->defnum = w->obj_num++;
	c->is_invisible = 0;
	c = ft_metal_alb(c, line, w, c);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(c, sizeof(t_cylinder)));
	w->obj_num++;
	free(c);
	return (0);
}
