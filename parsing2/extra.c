/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:18:14 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:49:49 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

//to comment or remove
void	ft_print_vec3d(t_vec3_d v)
{
	printf("x: [%f, ", v.x);
	printf("y: %f, ", v.y);
	printf("z: %f] ", v.z);
}

void	ft_print_vec2d(t_vec2_d v)
{
	printf("x: [%f, ", v.x);
	printf("y: %f] ", v.y);
}

void	ft_print_window(t_window *w)
{
	for (size_t i = 0; w && w->rt && w->rt[i]; i++)
		printf("rt: %s\n", w->rt[i]);
	if (w && w->ambient.id)
	{
		printf("ambient id: [%c]\n", w->ambient.id);
		printf("value: [%f] ", w->ambient.value);
		printf("color: ");
		ft_print_vec3d(w->ambient.color);
	}
	if (w && w->cam.id)
	{
		printf("camera id: %d\n", w->cam.id);
		printf("pos: ");
		ft_print_vec3d(w->cam.pos);
		printf("lookat: ");
		ft_print_vec3d(w->cam.lookat);
		printf("rtn: ");
		ft_print_vec2d(w->cam.rtn);
		printf("fov: %f\n", w->cam.fov);
	}
	for (; w->scene; w->scene = w->scene->next)
	{
		if (w->scene->content)
		{
			t_gameobject *go = w->scene->content;
			printf("type: %d\n", go->type);
			printf("pos: ");
			ft_print_vec3d(go->trs.pos);
			printf("rtn: ");
			ft_print_vec3d(go->trs.rtn);
			printf("scl: ");
			ft_print_vec3d(go->trs.scl);
			printf("color: ");
			ft_print_vec3d(go->color);
			printf("is_invisible: %c ", go->is_invisible);
			printf("metalness: %f ", go->mtlnss);
		}
	}
}
