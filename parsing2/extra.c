/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:18:14 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 20:31:31 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int DELETE_ORCOMMENT_THEFILE;

//to comment or remove
void	ft_print_vec3d(t_vec3_d v)
{
	printf("[x:%.1f, ", v.x);
	printf("y:%.1f, ", v.y);
	printf("z:%.1f] ", v.z);
}

void	ft_print_vec2d(t_vec2_d v)
{
	printf("[x:%.1f, ", v.x);
	printf("y:%.1f] ", v.y);
}

void	ft_print_window(t_window *w)
{
	for (size_t i = 0; w && w->rt && w->rt[i]; i++)
		printf("rt:%s\n", w->rt[i]);
	if (w && w->ambient.id)
	{
		printf("%sambient id [%c]:",KRED, w->ambient.id);
		printf("%svalue:[%.1f] ",KNRM, w->ambient.value);
		printf("color:");
		ft_print_vec3d(w->ambient.color);
		printf("\n");
	}
	if (w && w->cam.id)
	{
		printf("%scamera id %d:",KCYN, w->cam.id);
		printf("%spos:",KNRM);
		ft_print_vec3d(w->cam.pos);
		printf("lookat:");
		ft_print_vec3d(w->cam.lookat);
		printf("rtn:");
		ft_print_vec2d(w->cam.rtn);
		printf("fov:%.1f\n", w->cam.fov);
	}
	for (t_list *tmp = w->lights; tmp; tmp = tmp->next)
	{
		if (tmp->content)
		{
			t_lantern *l = (t_lantern*)tmp->content;
			printf("%slight:",KYEL);
			printf("%spos:",KNRM);
			ft_print_vec3d(l->pos);
			printf("value:%.1f ", l->intensity);
			printf("color:");
			ft_print_vec3d(l->color);
			printf("\n");
		}
	}	
	for (t_list *tmp = w->scene; tmp; tmp = tmp->next)
	{
		if (tmp->content)
		{
			t_gameobject *go = tmp->content;
			printf("%stype:",KGRN);
			switch (go->type)
			{
			case SPHERE:
				printf("SPHERE\n");
				break;
			case PLANE:
				printf("PLANE\n");
				break;
			case CYLINDER:
				printf("CYLINDER\n");
				break;
			default:
				break;
			}
			printf("%spos:",KNRM);
			ft_print_vec3d(go->trs.pos);
			printf("rtn:");
			ft_print_vec3d(go->trs.rtn);
			printf("scl:");
			ft_print_vec3d(go->trs.scl);
			printf("color:");
			ft_print_vec3d(go->color);
			if (go->is_invisible)
				printf("is_invisible:YES ");
			else
				printf("is_invisible:NO ");
			printf("metalness:%.1f \n", go->mtlnss);
			printf("defnum:%d\n", go->defnum);
		}
	}
}
