/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:57:16 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 19:43:55 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_pl(t_window *w, char *l)
{
	t_plane		*pl;
	t_vec3_d	tmp;

	l += 2;
	pl = ft_calloc(1, sizeof(t_plane));
	pl->type = PLANE;
	bypass_space(&l, w, pl);
	pl->trs.pos = ft_ato3d(&l, w, pl);
	bypass_space(&l, w, pl);
	tmp = ft_ato3d(&l, w, pl);
	if (tmp.x < -1 || tmp.x > 1
		|| tmp.y < -1 || tmp.y > 1
		|| tmp.z < -1 || tmp.z > 1)
		ft_print_error("ERR_PLANE -1<x<1", w, pl);
	pl->trs.rtn = v3d_normalize(tmp);
	bypass_space(&l, w, pl);
	pl->color = ft_rgb_convert(&l, w, pl);
	pl->mtlnss = ft_metalness_convert(&l, w, pl);
	pl->defnum = w->obj_num++;
	ft_lstadd_front(&w->scene, ft_lstnew_dup(pl, sizeof(t_plane)));
	w->obj_num++;
	ft_free((void **)&pl);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}
