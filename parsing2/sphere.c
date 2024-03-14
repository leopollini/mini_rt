/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:16:26 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 19:44:10 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"


// to add free in object
void	ft_parse_sp(t_window *w, char *l)
{
	t_sphere	*sp;


	//handle object initialisation
	/*
		double		mtlnss;
	double		albedo;
	t_color_3	color;
	t_transform	trs;
	int			defnum;
	char		*text;
	t_texture	texture;
	char		is_invisible;

	typedef struct s_transform
{
	t_point_3	pos;
	t_vec3_d	rtn;
	t_vec3_d	scl;
}				t_transform;
	*/
	l += 2;
	sp = ft_calloc(1, sizeof(t_sphere));
	sp->type = SPHERE;
	bypass_space(&l, w, sp);
	sp->trs.pos = ft_ato3d(&l, w, sp);
	bypass_space(&l, w, sp);
	sp->trs.scl.x = ft_atod_shift(&l) / 2;
	sp->trs.scl.y = sp->trs.scl.x;
	sp->trs.scl.z = sp->trs.scl.x;
	if (sp->trs.scl.x <= 0)
		ft_print_error(ERR_SPHERE, w, sp);
	bypass_space(&l, w, sp);
	sp->color = ft_rgb_convert(&l, w, sp);
	sp->mtlnss = ft_metalness_convert(&l, w, sp);
	sp->defnum = w->obj_num++;
	ft_lstadd_front(&w->scene, ft_lstnew_dup(sp, sizeof(t_sphere)));
	w->obj_num++;
	ft_free((void **)&sp);
	if (l[0] != 0)
		ft_print_error(ERR_ID, w, NULL);
}
