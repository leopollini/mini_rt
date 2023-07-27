/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/28 00:14:09 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H

# define MINI_RT_H

# define EXITVAL 10
# define LN_ACCURACY 50
# define MAX_ITER 80
# define SQR_RAD 100
# define CHANGE_VAL 0.25f
# define E_0 0.1f
# define E_N1 0.01f
# define E_N2 0.001f
# define SCALE_S 1.1f
# define SCALE_L 2.2f
# define SCALE_LL 12
# define SQRT2 1.414214
# define SQRT3 1.732051
# define MAX_INT 0x7fffffff
# define START_AA_VAL 3

# define M_PI          3.141592653589793238462643383279502884L

# define CREAT_GB_SWITCH 0

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>

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
typedef struct s_vec3_c
{
	char	x;
	char	y;
	char	z;
}				t_vec3_c;
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

/*    //ALIASES\\    */
typedef t_vec3_d	t_point_3;
typedef t_vec3_c	t_color_3;

/*    //CAMERA STRUCTURE\\    */
typedef struct s_camera
{
	t_vec3_d		pos;
	t_vec3_d		lookat;
	t_vec3_d		hori;
	t_vec3_d		vert;
	t_vec3_d		util;
	double			focal_len;
	t_vec2_d		scene_window;
	double			fov;
}				t_camera;

/*    //ALL PURPOSE STRUCTURE\\    */
typedef struct s_window
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_data			skybox;
	t_vec2_i		skybox_size;
	t_vec2_i		size;
	t_camera		cam;
	t_list			*scene;
	int				obj_num;
	t_list			*lights;
	int				anti_aliasing;
	char			toggle_hd;
}				t_window;

/*    //ENUMS\\    */
typedef enum e_tracing_mode
{
	OCCLUSION = 0,
	COLOR,
	REFLECT,
	LIGHT,
	OBJECTS,
	ALL
}				t_tracing_mode;

typedef enum e_objtype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
}				t_objtype;

/*    //SCENE OBJECTS\\    */
typedef struct s_lantern
{
	t_vec3_d		pos;
	t_vec3_d		lookat;
	t_vec3_d		color;
	float			intensity;
}				t_lantern;

/*    //GAMEOBJECTS\\    */
typedef struct s_transform
{
	t_point_3	position;	// double x, y, z
	t_vec3_d	rotation;	// double x, y, z {MUST BE NORMALIZED}
	t_vec3_d	scale;		// x, y, z > 0
}				t_transform;

typedef struct s_gameobject
{
	double		albedo;		// [0, 1]
	t_color_3	color;		// int x, y, z [0, 255]
	t_transform	transform;	// see t_transform
	t_objtype	type;		// see enum objtype
}				t_gameobject;

/*    //RAY STRUCTURES\\    */
typedef struct s_raydata
{
	t_vec3_d		color;
	t_vec3_d		hit_point;
	t_gameobject	*hit_pointer;
	char			hit_something;
	t_vec3_d		point_normal;
	double			sqr_distance;
}				t_raydata;

typedef struct s_ray
{
	t_raydata		data;
	t_vec3_d		direction;
	t_tracing_mode	mode;
	t_vec3_d		source;
}				t_ray;

/*    //FUNCTIONS\\    */
int			win_close(t_window *win);
int			manage_keys(int keypressed, t_window *win);
int			manage_mouse(int button, int x, int y, t_window *win);
int 		rft_init_scene();
void		my_image_creator(t_window *w);
void		my_mlx_pixel_put(t_data *data, int x, int y, int cl);
void		reimage(t_window *win);
t_vec3_d	create_argb(int r, int g, int b);
t_vec3_d	create_argb_s(double r, double g, double b);
int			create_trgb(int a, int r, int g, int b);
int			create_trgb_s(double a, double r, double g, double b);
void		camera_update(t_window *w);
int			pull_argb(t_vec3_d c, int div);
char		rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode);
t_vec3_d	skybox_calc(t_ray r, t_window *w);
t_vec3_d	rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);

void	transform_out(t_transform t);
/*    //VECTOR METHODS\\    */
t_vec2_i	new_v2_i(int x, int y);
t_vec3_i	new_v3_i(int x, int y, int z);
t_vec2_d	new_v2_d(double x, double y);
t_vec3_d	new_v3_d(double x, double y, double z);
t_vec3_d	v3_normalize(t_vec3_d in);
t_vec2_d	v2_d_sum(int n, ...);
t_vec3_d	v3_d_sum(int n, ...);
t_vec3_d	v3d_anti(t_vec3_d a);
t_vec2_d	v2d_anti(t_vec2_d a);
double		v3_d_dot(t_vec3_d a, t_vec3_d b);
t_vec3_d	v3d_cross(t_vec3_d a, t_vec3_d b);
t_vec3_d	v3_d_scal(t_vec3_d a, double b);
t_vec3_d	ray_at(t_ray r, double t);
void		v3d_out(t_vec3_d a);
double		v3_d_sqr_mod(t_vec3_d a);
t_vec3_d	color_add(t_vec3_d a, const t_vec3_d b);

#endif
