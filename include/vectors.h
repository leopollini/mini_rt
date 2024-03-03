/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/03 21:45:11 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# include <stdarg.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

/*    //VECTOR STRUCTURES\\    */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bps;
	int		ll;
	int		en;
}				t_data;

typedef struct s_vec2_i
{
	int	x;
	int	y;
}				t_vec2_i;

typedef struct s_vec3_i
{
	int	x;
	int	y;
	int	z;
}				t_vec3_i;

typedef struct s_vec2_d
{
	double	x;
	double	y;
}				t_vec2_d;

typedef struct s_vec3_d
{
	double	x;
	double	y;
	double	z;
}				t_vec3_d;

/*    //VECTOR3 ALIASES\\    */
typedef t_vec3_d	t_point_3;
typedef t_vec3_d	t_color_3;

/*    //VECTOR METHODS\\    */

/* vectors_new.c */
t_vec2_i		new_v2_i(int x, int y);
t_vec3_i		new_v3_i(int x, int y, int z);
t_vec2_d		new_v2d(double x, double y);
t_vec3_d		new_v3d(double x, double y, double z);

/* vector3_ops.c */
t_vec3_d		v3d_scal(t_vec3_d a, double b);
double			v3d_dot(t_vec3_d a, t_vec3_d b);
t_vec3_d		v3d_cross(t_vec3_d a, t_vec3_d b);
double			v3d_sqr_mod(t_vec3_d a);
double			v3d_mod(t_vec3_d a);

/* vector3_ops_2.c */
t_vec3_d		v3d_sumponder(t_vec3_d a, t_vec3_d b, double p);
t_vec3_d		v3d_sum_2(t_vec3_d a, t_vec3_d b);
t_vec3_d		v3d_sub(t_vec3_d a, t_vec3_d b);
t_vec3_d		v3d_sum(int n, ...);
t_vec3_d		v3d_anti(t_vec3_d a);

/* miscellaneous.c */
t_vec2_d		v2d_anti(t_vec2_d a);
t_vec3_d		v3d_specular(t_vec3_d v, t_vec3_d normal);
t_vec3_d		v3d_normalize(t_vec3_d in);
void			v3d_out(t_vec3_d a);

/* miscellaneous_2.c */
t_vec3_d		color_add(t_vec3_d a, const t_vec3_d b);
t_color_3		color_3_merge(t_color_3 a, t_color_3 b);
double			plian_module(double a);
t_vec2_d		v2d_sum(int n, ...);
void			v3d_add(t_vec3_d *a, t_vec3_d b);

#endif
