/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:57:49 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/18 15:32:12 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	char	*ptr;

	ptr = &c;
	write(1, ptr, 1);
}

void	ft_putchar_fd(char c, int fd)
{
	char	*ptr;
	size_t	cont;

	ptr = &c;
	cont = 1;
	write(fd, ptr, cont);
}
