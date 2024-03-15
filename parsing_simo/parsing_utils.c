/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:42 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 13:51:16 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

// to add free in object
void	bypass_space(char **str, t_window *w, void *data)
{
	if (str && *str && ft_isspace(**str))
		while (*str && ft_isspace(**str))
			(*str)++;
	else
		ft_print_error(ERR_FPARAM, w, data);
}
