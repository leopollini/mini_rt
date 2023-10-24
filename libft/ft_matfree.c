/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:24:29 by iragusa           #+#    #+#             */
/*   Updated: 2023/03/14 23:24:55 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	free_mat(char **matrix)
{
	int	y;

	y = 0;
	if (matrix)
	{
		while (matrix[y] != NULL)
		{
			free(matrix[y]);
			y++;
		}
		free (matrix);
	}
	return (0);
}
