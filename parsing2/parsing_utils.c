/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:42 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/14 22:49:54 by sdel-gra         ###   ########.fr       */
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

t_list	*ft_lstnew_dup(const void *a, int size)
{
	void	*temp;
	int		i;

	i = -1;
	temp = malloc(size);
	while (++i < size)
		((char *)temp)[i] = ((char *)a)[i];
	return (ft_lstnew(temp));
}
