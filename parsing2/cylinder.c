/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:02:00 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 16:36:13 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	ft_1(double n)
{
	if (n < -1 || n > 1)
		return (1);
	return (0);
}

// da ridurre
void	ft_parse_cy(t_window *w, char *l)
{
	t_cylinder	*cy;

	cy = ft_calloc(1, sizeof(t_cylinder));
	cy->type = CYLINDER;
	l += 2;
	bypass_space(&l, w, cy);
	cy->trs.pos = ft_ato3d(&l, w, cy);
	bypass_space(&l, w, cy);
	cy->trs.rtn = ft_ato3d(&l, w, cy);
	if (ft_1(cy->trs.rtn.x) || ft_1(cy->trs.rtn.y) || ft_1(cy->trs.rtn.z))
		ft_print_error("ERR_CYLINDER -1<x<1", w, cy);
	bypass_space(&l, w, cy);
	cy->trs.scl.x = ft_atod_shift(&l);
	if (cy->trs.scl.x <= 0)
		ft_print_error("ERR_CYLINDER diameter must be > 0", w, cy);
	bypass_space(&l, w, cy);
	cy->trs.scl.y = ft_atod_shift(&l);
	if (cy->trs.scl.y <= 0)
		ft_print_error("ERR_CYLINDER altezza must be > 0", w, cy);
	bypass_space(&l, w, cy);
	cy->color = ft_rgb_convert(&l, w, cy);
	cy->mtlnss = ft_metalness_convert(&l, w, cy);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(cy, sizeof(t_cylinder)));
	w->obj_num++;
	ft_free((void **)cy);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}
