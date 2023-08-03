/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/31 16:59:10 by lpollini         ###   ########.fr       */
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
# define SCALE_S 1.3f
# define SCALE_L 2.2f
# define SCALE_LL 12
# define SQRT2 1.414214
# define SQRT3 1.732051
# define MAX_INT 0x7fffffff
# define START_AA_VAL 3
# define NEGATIVE_LIM -0.0000000001
# define POSITIVE_LIM 0.0000000001
# define M_PI 3.141592653589793238462643383279502884L
# define MAX_REF_DEPTH 5

# define THREADS 10

# define CREAT_GB_SWITCH 0

/*error msg*/

# define NOARGS "something's wrong, you have to write: ./minirt scenes/mandatory.c"
# define NOFILE "sorry, file not exist!"
# define NO_RT "ehy dude, only rt file!"
# define NO_LIGHT "check your params! missing light data"
# define NO_CAM "check your params! missing camera data"
# define NO_AMBIENT "check your params! missing ambient data"

# include "libft.h"
# include "mlx.h"
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
typedef	char	bool;

/*    //CAMERA STRUCTURE\\    */
typedef struct s_camera
{
	char			id;
	t_vec3_d		pos;
	t_vec3_d		lookat;
	t_vec3_d		hori;
	t_vec3_d		vert;
	t_vec3_d		util;
	double			focal_len;
	t_vec2_d		scene_window;
	double			fov;
}				t_camera;

typedef struct s_ambient
{
	char			id;
	t_vec3_d		pos;
}				t_ambient;

typedef struct s_light
{
	char			id;
	t_vec3_d		pos;
}				t_light;


/*    //ENUMS\\    */
typedef enum e_tracing_mode
{
	OCCLUSION = 0,
	LIGHT,
	REFERENCE,
	COLOR,
	REFLECT,
	OBJECTS,
	ALL
}				t_tracing_mode;

typedef enum e_objtype
{
	SPHERE = 0,
	PLANE,
	CYLINDER,
	METAL,
	METALPLANE,
	METALSPHERE
}				t_objtype;

/*    //SCENE OBJECTS\\    */
typedef struct s_lantern
{
	t_vec3_d		pos;
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
	double		metalness;	// [0, 1]
	double		albedo;		// [0, 1]
	t_color_3	color;		// int x, y, z [0, 255]
	t_transform	transform;	// see t_transform
	t_objtype	type;		// see enum objtype
	int			defnum;
}				t_gameobject;

typedef t_gameobject	t_sphere;
typedef t_gameobject	t_cylinder;
typedef t_gameobject	t_plane;

/*    //RAY STRUCTURES\\    */
typedef struct s_raydata
{
	t_vec3_d		color;
	t_vec3_d		metalcolor;
	t_vec3_d		hit_point;
	t_gameobject	*hit_pointer;
	bool			hit_something;
	t_vec3_d		point_normal;
	double			sqr_distance;
	char			ismetal;
}				t_raydata;

typedef struct s_ray
{
	t_raydata		data;
	t_vec3_d		direction;
	t_tracing_mode	mode;
	t_vec3_d		source;
	double			max_sqr_len;
	char			depth;
}				t_ray;

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
	t_ambient		ambient;
	t_light			light;
	t_list			*scene;
	int				obj_num;
	t_list			*lights;
	int				anti_aliasing;
	bool			toggle_hd;
	t_gameobject	*selected;
	double			step;
	char			do_exit;
	int				num_line;
}				t_window;

/*    //THREAD STRUCTURE\\    */

typedef struct s_thread
{
	int			i;
	int			j;
	t_window	*w;
}				t_thread;

/*    //FUNCTIONS\\    */
int				win_close(t_window *win);
int				manage_keys(int keypressed, t_window *win);
int				manage_mouse(int button, int x, int y, t_window *win);
int 			rft_init_scene();
void			my_image_creator(t_window *w);
void			my_mlx_pixel_put(t_data *data, int x, int y, int cl);
void			reimage(t_window *win);
t_vec3_d		create_argb(int r, int g, int b);
t_vec3_d		create_argb_s(double r, double g, double b);
int				create_trgb(int a, int r, int g, int b);
int				create_trgb_s(double a, double r, double g, double b);
void			camera_update(t_window *w);
int				pull_argb(t_vec3_d c, int div);
char			rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode);
t_vec3_d		skybox_calc(t_ray r, t_window *w);
t_vec3_d		rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);
unsigned int	my_mlx_pixel_get(t_data data, int x, int y);
t_vec3_d		rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);
int				rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp, t_ray *r, t_window *w);
void			rft_window_cast(t_window *w);
void			my_image_creator(t_window *w);

void			transform_out(t_transform t);
/*    //VECTOR METHODS\\    */

/*file color_opers.c*/

t_vec3_d 		create_argb_s(double r, double g, double b);
int 			create_trgb_s(double a, double r, double g, double b);
int				create_trgb(int a, int r, int g, int b);
int 			pull_argb(t_vec3_d c, int div);
t_vec3_d 		create_argb(int r, int g, int b);
void 			reimage(t_window *win);
void			my_mlx_pixel_put(t_data *data, int x, int y, int cl);
unsigned int	my_mlx_pixel_get(t_data data, int x, int y);

/*file image_creat.c*/

t_vec3_d		skybox_calc(t_ray r, t_window *w);
int				hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode);
int				hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode);
int				hit_cylinder(t_cylinder *cylinder, t_ray *r, t_tracing_mode mode);
int				type_sorter(t_objtype t, t_gameobject *obj, t_ray *r, t_tracing_mode mode);
char			rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode);
t_color_3		rft_specular(t_ray *r, t_ray *lr, t_lantern *l, double lambda);
t_color_3 		rft_diffuse(t_ray *r, t_ray *o, t_lantern *l);
t_vec3_d		rft_search_light(t_window *w, t_ray *r, t_tracing_mode mode);
t_vec3_d		rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);

/*file input.c*/

int				win_close(t_window *win);
//static int		keys_manager_1(t_window *win, int keypressed);
//static int		keys_manager_2(t_window *win, int keypressed);
int				manage_keys(int keypressed, t_window *win);
int				manage_mouse(int button, int x, int y, t_window *w);

/*file palle.c*/

int				rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp, t_ray *r, t_window *w);
void			*build_pt(t_window *w, int i, int j);
void			*thread_lol(void *a);
void			init_threads(t_window *w);
void			rft_window_cast(t_window *w);
void 			my_image_creator(t_window *w);

/*file rft_init_scene.c*/

int 			rft_init_scene();

/*file utils.c*/

t_raydata		unpack_ray(void *a);

/*file vectors.c*/

void			v3d_out(t_vec3_d a);
void			transform_out(t_transform t);
t_vec2_i		new_v2_i(int x, int y);
t_vec3_i		new_v3_i(int x, int y, int z);
t_vec2_d		new_v2_d(double x, double y);
t_vec3_d		new_v3_d(double x, double y, double z);
t_vec3_d		v3_normalize(t_vec3_d in);
t_vec3_d		v3d_anti(t_vec3_d a);
t_vec2_d		v2d_anti(t_vec2_d a);
t_vec3_d		v3_d_scal(t_vec3_d a, double b);
t_vec3_d		ray_at(t_ray r, double t);
double			v3_d_dot(t_vec3_d a, t_vec3_d b);
double			v3_d_sqr_mod(t_vec3_d a);
t_vec2_d		v2_d_sum(int n, ...);
t_vec3_d		v3_d_sum_2(t_vec3_d a, t_vec3_d b);
t_vec3_d		v3_d_sum(int n, ...);
t_vec3_d		v3d_cross(t_vec3_d a, t_vec3_d b);
t_vec3_d		color_add(t_vec3_d a, const t_vec3_d b);
t_color_3		color_3_merge(t_color_3 a, t_color_3 b);
t_vec3_d		v3_d_sumponder(t_vec3_d a, t_vec3_d b, double p);
t_vec3_d		v3_d_specular(t_vec3_d v, t_vec3_d normal);
double			plan_module(double a);
double			v3_d_mod(t_vec3_d a);

/*file parse_utils.c*/

int				ft_print_error(char *err);

/*file file_rt.c*/

int				ft_check_data(t_window *w);
int				ft_check_file(char *scene);
int				ft_read_rt(t_window *w, int fd);
int				ft_open_rt(t_window *w, char *scene);

/*file parsing.c*/



#endif
