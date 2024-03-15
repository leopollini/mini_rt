/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:02:00 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 14:21:14 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	ft_1(double n)
{
	if (n < -1 || n > 1)
		return (1);
	return (0);
}

double	ft_skip_double_error(char **l, t_window *w, void *obj, char *err)
{
	double	out;

	out = 0;
	bypass_space(l, w, obj);
	out = ft_atod_shift(l);
	if (out <= 0)
		ft_print_error(err, w, obj);
	return (out);
}

void	ft_parse_cy(t_window *w, char *l)
{
	t_cylinder	*cy;
	t_vec3_d	tmp;

	cy = ft_calloc(1, sizeof(t_cylinder));
	cy->type = CYLINDER;
	l += 2;
	bypass_space(&l, w, cy);
	cy->trs.pos = ft_ato3d(&l, w, cy);
	bypass_space(&l, w, cy);
	tmp = ft_ato3d(&l, w, cy);
	if (ft_1(tmp.x) || ft_1(tmp.y) || ft_1(tmp.z))
		ft_print_error(ERR_RANGE, w, cy);
	cy->trs.rtn = v3d_normalize(tmp);
	cy->trs.scl.x = ft_skip_double_error(&l, w, cy, ERR_CYLINDER);
	cy->trs.scl.y = ft_skip_double_error(&l, w, cy, ERR_CYLINDER);
	bypass_space(&l, w, cy);
	cy->color = ft_rgb_convert(&l, w, cy);
	cy->defnum = w->obj_num++;
	cy->mtlnss = ft_metalness_convert(&l, w, cy);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(cy, sizeof(t_cylinder)));
	w->obj_num++;
	ft_free((void **)&cy);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}
