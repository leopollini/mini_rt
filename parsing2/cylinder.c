/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:02:00 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:49:11 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_cy(t_window *w, char *l)
{
	t_cylinder	*cy;

	cy = ft_calloc(1, sizeof(t_cylinder));
	cy->type = CYLINDER;
	bypass_space(&l, w);
	cy->trs.pos = ft_ato3d(&l, w);
	bypass_space(&l, w);
	// normalizzato che vordi?
	cy->trs.rtn = ft_ato3d(&l, w);
	if (cy->trs.rtn.x < -1 || cy->trs.rtn.x > 1
		|| cy->trs.rtn.y < -1 || cy->trs.rtn.y > 1
		|| cy->trs.rtn.z < -1 || cy->trs.rtn.z > 1)
		ft_print_error("ERR_CYLINDER -1<x<1", w, cy);
	bypass_space(&l, w);
	//dove lo metto il diametro?
	bypass_space(&l, w);
	//dove metto l'altezza?
	bypass_space(&l, w);
	cy->color = ft_rgb_convert(&l, w);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(cy, sizeof(t_cylinder)));
	w->obj_num++;
	ft_free((void **)cy);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}