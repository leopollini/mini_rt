/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:45:33 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/08 14:18:46 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

int	ft_print_error(char *err, t_window *w, void *del)
{
	write(2, "Error\n ", 7);
	ft_putstr_fd(err, 2);
	write(2, "\n", 1);
	//if (w->rt != NULL)
		//free_mat(w->rt);
	ft_lstclear((&w->lights), free);
	//free_obj(w->scene);
	if (del != NULL)
		free(del);
	exit (1);
}

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
	//da rimuovere
	//for (int i = 0; w->rt[i]; i++)
	//	printf("%s\n", w->rt[i]);
	ft_check_parse_data(w);
	return (0);
}