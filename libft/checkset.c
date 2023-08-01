/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:24:02 by iragusa           #+#    #+#             */
/*   Updated: 2023/02/12 16:24:11 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	findchar(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	checkset(char *str, char *set)
{
	while (*str)
	{
		if (!findchar(*str, set))
			return (0);
		str++;
	}
	return (1);
}

/*int main ()
{
	char	*s1 = "00C0EE10101PEPPPPEEEEEE";
	char	*set = "01PCE";
	
	printf("%d\n", checkset(s1, set));
	return (0);
}*/
