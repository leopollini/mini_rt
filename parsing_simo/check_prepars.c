/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_prepars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:09:23 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/15 13:06:08 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_rt.h"

void	ft_check_scp(char *rt_line, int *j)
{
	if (!ft_strncmp(rt_line, "Sp", 2))
		j[4]++;
	if (!ft_strncmp(rt_line, "Pl", 2))
		j[5]++;
	if (!ft_strncmp(rt_line, "Cy", 2))
		j[6]++;
	if (!ft_strncmp(rt_line, "sp", 2))
		j[7]++;
	if (!ft_strncmp(rt_line, "pl", 2))
		j[8]++;
	if (!ft_strncmp(rt_line, "cy", 2))
		j[9]++;
}

void	ft_check_acl(char *rt_line, int *j)
{
	if ((rt_line[0] == 'A'))
		j[0]++;
	if ((rt_line[0] == 'C'))
		j[1]++;
	if ((rt_line[0] == 'L'))
		j[2]++;
	if ((rt_line[0] == 'l'))
		j[3]++;
}

int	ft_objn(int once, int inf)
{
	if ((once == 1 && inf != 0) || (once > 1))
		return (1);
	return (0);
}

// j = {A,C,L,l,sp,cy,pl,SP,CY,PL}
void	ft_check_parse_data(t_window *w)
{
	int	i;
	int	j[10];

	i = 0;
	while (i < 10)
		j[i++] = 0;
	i = 0;
	while (w->rt[i])
	{
		ft_check_acl(w->rt[i], j);
		ft_check_scp(w->rt[i], j);
		i++;
	}
	if (j[0] != 1 || j[1] != 1 || ft_objn(j[2], j[3])
		|| (j[2] == 0 && j[3] == 0))
		ft_print_error(ACL_ERR, w, NULL);
	if (ft_objn(j[4], j[7]) || ft_objn(j[5], j[8]) || ft_objn(j[6], j[9]))
		ft_print_error(SPC_ERR, w, NULL);
	i = 0;
	while (w->rt[i])
		ft_parse_line(w, w->rt[i++]);
}
