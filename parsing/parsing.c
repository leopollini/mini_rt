/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 22:03:03 by iragusa           #+#    #+#             */
/*   Updated: 2023/07/27 22:03:07 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int ft_line_parser(w, line)
{
	if (ft_strncmp(line, "R", 1) == 0)
		return (parse_res(w, line));
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_amb(w, line));
	if (ft_strncmp(line, "C", 1) == 0)
		return (parse_cam(w, line, 0));
	if (ft_strncmp(line, "L", 1) == 0)
		return (parse_light(w, line));
	if (ft_strncmp(line, "sp", 2) == 0)
		return (parse_obj(w, line, SPHERE));
	if (ft_strncmp(line, "pl", 2) == 0)
		return (parse_obj(w, line, PLANE));
	if (ft_strncmp(line, "cy", 2) == 0)
		return (parse_obj(w, line, CYLINDER));
	if (ft_strncmp(line, "msp", 3) == 0)
		return (parse_obj(w, line, METALSPHERE));
    if (ft_strncmp(line, "mpl", 3) == 0)
        return (parse_obj(w, line, METALPLANE));
	return (0);
}
