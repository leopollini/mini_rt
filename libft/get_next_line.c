/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:27:27 by iragusa           #+#    #+#             */
/*   Updated: 2022/11/20 14:30:43 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_line_help(char *ret, char *ptr, int i)
{
	ptr[i] = ret[i];
	i++;
	return (i);
}

char	*ft_read(int fd, char *ret)
{
	char	*buf;
	int		num;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (!ret)
		ret = NULL;
	num = 1;
	while (!ft_findchar('\n', ret) && num != 0)
	{
		num = read(fd, buf, BUFFER_SIZE);
		if (num == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[num] = '\0';
		ret = ft_strjoin2(ret, buf);
	}
	free(buf);
	return (ret);
}

char	*ft_line(char *ret)
{
	char	*ptr;
	int		i;

	i = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	ptr = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (ret[i] && ret[i] != '\n')
		i = ft_line_help(ret, ptr, i);
	if (ret[i] == '\n')
		i = ft_line_help(ret, ptr, i);
	ptr[i] = '\0';
	if (ptr[0] == 0 || !ptr)
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

char	*ft_next_ret(char *ret)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ret[i] && ret[i] != '\n')
		i++;
	if (!ret[i] || !ret || ret[0] == 0)
	{
		free(ret);
		return (NULL);
	}
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(ret) - i + 1));
	if (!ptr)
		return (NULL);
	i++;
	while (ret[i])
		ptr[j++] = ret[i++];
	ptr[j] = '\0';
	free(ret);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ret;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0))
	{
		if (ret != NULL)
		{	
			free(ret);
			ret = NULL;
		}
		return (NULL);
	}
	ret = ft_read(fd, ret);
	if (!ret)
		return (NULL);
	line = ft_line(ret);
	ret = ft_next_ret(ret);
	return (line);
}

/*int	main(void)
{
	char *temp;
	char *temp2;
	char *temp3;
	char *temp4;
	int file_descriptor = open("prova", O_RDONLY);
	//printf("file_descriptor: %d \n", file_descriptor);
	temp = get_next_line(file_descriptor);
	temp2 = get_next_line(file_descriptor);
	temp3 = get_next_line(file_descriptor);
	temp4 = get_next_line(file_descriptor);
	printf("%s", temp);
	free(temp);
	printf("%s", temp2);
	free(temp2);
	printf("%s", temp3);
	free(temp3);
	printf("%s", temp4);
	free(temp4);
	return (0);
}*/
