/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:15 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/08 14:16:11 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_free(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_find_substr(const char *str, const char *sub_str)
{
	int	i;
	int	i_sub;

	i = ft_strlen(str) - ft_strlen(sub_str);
	i_sub = 0;
	if (i < 0 && str && sub_str)
		return (0);
	while (str[i] && sub_str[i_sub])
	{
		if (str[i] != sub_str[i_sub])
			return (0);
		if (str[i + 1] == '\0' && sub_str[i_sub + 1] == '\0')
			return (1);
		i++;
		i_sub++;
	}
	return (0);
}

int	ft_strchr_i(const char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (!c && !s)
	{
		return (0);
	}
	if (s && s[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	out = ft_calloc(ft_strchr_i(s1, '\0') + ft_strchr_i(s2, '\0') + 1, 1);
	if (!out)
		return (NULL);
	while (s1 && s1[i] != 0)
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != 0)
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	ft_free((void **)&s1);
	return (out);
}
