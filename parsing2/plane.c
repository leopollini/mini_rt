/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:57:16 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:51:59 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_pl(t_window *w, char *l)
{
	t_plane	*pl;

	pl = ft_calloc(1, sizeof(t_plane));
	pl->type = PLANE;
	bypass_space(&l, w);
	pl->trs.pos = ft_ato3d(&l, w);
	bypass_space(&l, w);
	// normalizzato che vordi?
	pl->trs.rtn = ft_ato3d(&l, w);
	if (pl->trs.rtn.x < -1 || pl->trs.rtn.x > 1
		|| pl->trs.rtn.y < -1 || pl->trs.rtn.y > 1
		|| pl->trs.rtn.z < -1 || pl->trs.rtn.z > 1)
		ft_print_error("ERR_PLANE -1<x<1", w, pl);
	bypass_space(&l, w);
	pl->color = ft_rgb_convert(&l, w);
	ft_lstadd_front(&w->scene, ft_lstnew_dup(pl, sizeof(t_plane)));
	w->obj_num++;
	ft_free((void **)pl);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}