/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:58 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/12 19:05:12 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_parse_line(t_window *w, char *l)
{
	if (l[0] == 'A')
		ft_parse_ambient(w, l);
	else if (l[0] == 'C')
		ft_parse_cam(w, l);
	else if (l[0] == 'L' || l[0] == 'l')
		ft_parse_light(w, l);
	else if ((l[0] == 'S' || l[0] == 's') && l[1] == 'p')
		ft_parse_sp(w, l);
	else if ((l[0] == 'P' || l[0] == 'p') && l[1] == 'l')
		ft_parse_pl(w, l);
	else if ((l[0] == 'C' || l[0] == 'c') && l[1] == 'y')
		ft_parse_cy(w, l);
	else
		ft_print_error(ERR_ID, w, NULL);
}
