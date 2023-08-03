/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iragusa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:13:00 by iragusa           #+#    #+#             */
/*   Updated: 2023/07/31 20:13:08 by iragusa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

/*controllo estensione (-3 perche' tolgo ".rt")*/
int	ft_check_file(char *scene)
{
	size_t len;

	
	len = ft_strlen(scene) - 3;
	if (len > 3)
	{
		if (ft_strncmp(scene + len, ".rt", 3) == 0)
			return (1);
	}
	return (0);
}

int	ft_check_data(t_window *w)
{
	if (w->light.id)
		return (ft_print_error(NO_LIGHT));
	if (!w->cam.id)
		return (ft_print_error(NO_CAM));
	if (w->ambient.id)
		return (ft_print_error(NO_AMBIENT));
	
	return (0);
}

/*trasmormo i tab in spazi e dopo trimmo*/
char *ft_clean_str(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

/*leggo ogni riga, la pulisco e la parso, e controllo ci siano tutti i parametri*/
int	ft_read_rt(t_window *w, int fd)
{
	int		i;
	int		check;
	char	*line;

	
	check = 0;
	i = 0;
	while (check != 1)
	{
		i++;
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_clean_str(line);
		if (ft_line_parser(w, line))
			check = 1;
		free(line);
	}
	w->num_line = i;
	if (!check && ft_check_data(w))
		check = 1;
	close(fd);
	return (check);
}

/*apro il file passato, controllo l'estensione e lo mando alla lettura*/
int	ft_open_rt(t_window *w, char *scene)
{
	int	fd;

	fd = open(scene, O_RDONLY);
	if (fd == -1)
		return (ft_print_error(NOFILE));
	if (ft_check_file(scene) == 0)
		return (ft_print_error(NO_RT));
	if (ft_read_rt(w, fd))
		return (0);
	return (1);
}