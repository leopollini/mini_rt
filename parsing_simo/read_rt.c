/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:45:33 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 13:54:09 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_init_scene(t_window *w)
{
	w->scene = ft_lstnew(NULL);
	w->lights = ft_lstnew(NULL);
	w->obj_num = 0;
	w->num_line = 0;
	w->rt = NULL;
}

void	ft_read_filert(t_window *w, char *filert)
{
	int		fd;
	char	*line;
	char	*fullfile;

	fd = open(filert, O_RDONLY);
	if (fd < 0)
		ft_print_error(NOFILE, w, NULL);
	fullfile = ft_calloc(1, 1);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '#')
			fullfile = ft_strjoin_free(fullfile, line);
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	w->rt = ft_split(fullfile, '\n');
	ft_free((void **)&fullfile);
	ft_free((void **)&line);
	close(fd);
}

int	ft_open_rt(t_window *w, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_print_error(NOFILE, w, NULL));
	if (ft_find_substr(av[1], ".rt") == 0)
		return (ft_print_error(NO_RT, w, NULL));
	ft_init_scene(w);
	ft_read_filert(w, av[1]);
	ft_check_parse_data(w);
	return (0);
}
