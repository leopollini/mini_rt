/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:13:00 by iragusa           #+#    #+#             */
/*   Updated: 2023/10/10 18:28:48 by lpollini         ###   ########.fr       */
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
	int	i;

	i = 0;
	contchar(w);
	// checkobj(w);
	while (w->rt[i])
	{
		ft_line_parser(w, w->rt[i]);
		i++;
	}
	return 0;
}

/*leggo ogni riga, la pulisco e controllo ci siano tutti i parametri corretti*/

void	ft_read_rt(t_window *w, char *scene)
{
	char	*line;
	char	*full_rt;
	int		fd;
	

	w->num_line = 0;
	full_rt = ft_calloc(1, 1);
	fd = open(scene, O_RDONLY);
	if (fd < 0)
		ft_print_error(NOFILE, w);
	line = get_next_line(fd);
	while (line)
	{
		full_rt = ft_strjoin2(full_rt, line);
		free(line);
		line = get_next_line(fd);
		if (line)
			w->num_line++;
	}
	close(fd);
	free(line);
	w->rt = ft_split(full_rt, '\n');
	free(full_rt);
	ft_check_data(w);
}

/*apro il file passato, controllo l'estensione e lo mando alla lettura*/
int	ft_open_rt(t_window *w, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_print_error(NOFILE, w));
	if (ft_check_file(av[1]) == 0)
		return (ft_print_error(NO_RT, w));
	ft_read_rt(w, av[1]);
	return (0);
}

