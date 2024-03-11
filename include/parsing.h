/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:11:48 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/03/11 17:51:38 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "mini_rt.h"

typedef struct s_window	t_window;

/* basic_utils.c */
int			ft_isspace(char c);
char		*ft_strjoin_free(char *s1, char const *s2);
int			ft_strchr_i(const char *s, char c);
int			ft_find_substr(const char *str, const char *sub_str);
void		ft_free(void **ptr);

/* parsing.c */
void		ft_parse_line(t_window *w, char *rt_line);

/* check_prepars.c */
void		ft_check_parse_data(t_window *w);

/* parsing_utils.c */
void		bypass_space(char **str, t_window *w);

/* convert.c */
t_vec3_d	ft_ato3d(char **l, t_window *w);
double		ft_atod_shift(char **l);
t_vec3_d	ft_rgb_convert(char **l, t_window *w);


/* parsing_ambient.c */
void		ft_parse_ambient(t_window *w, char *l);

/* parsing_camera.c */
void		ft_parse_cam(t_window *w, char *l);

/* parsing_light.c */
void		ft_parse_light(t_window *w, char **l);

/* parsing_sphere.c */
void		ft_parse_sp(t_window *w, char *l);

/* parsing_plane.c */
void		ft_parse_pl(t_window *w, char *l);

/* parsing_cylinder.c */
void		ft_parse_cy(t_window *w, char *l);


#endif