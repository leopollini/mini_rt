/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2024/03/15 17:11:42 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define UNI_SCAL_LIGHT 1
# define EXITVAL 10
# define LN_ACCURACY 50
# define MAX_ITER 80
# define SQR_RAD 100
# define CHANGE_VAL 0.25f
# define E_0 0.1f
# define E_N1 0.01f
# define E_N2 0.001f
# define SCALE_S 1.2f
# define SCALE_L 2.2f
# define SCALE_LL 12
# define SQRT2 1.414214
# define SQRT3 1.732051
# define MAX_INT 0x7fffffff
# define START_AA_VAL 4
# define NEGATIVE_LIM -0.0000000001
# define POSITIVE_LIM 0.0000000001
# define M_PI 3.141592653589793238462643383279502884L
# define MAX_REF_DEPTH 3
# define ROT_CONST 3

# define CREAT_GB_SWITCH 0

# define IMGSIZE 400
# define SKYBOX "skybox/universe.xpm"

# define NOARGS "check input, write:./minirt scenes/mandatory.rt"
# define NOSIZE "the last two args are size of win, so they can be only digits!"
# define NOINIT "something's wrong during initialization, try again"
# define NOFILE "no such file!"
# define NO_RT "ehy dude, only .rt file!"
# define MALLOC "oh no, error in malloc() on memory allocation"
# define ACL_ERR "check file rt! need 1 A, 1 C, at least 1 L and at most 1 R!"
# define CHECK_RT ",check your params!"

# include "../.mlx/mlx.h"
# include "libft.h"
# include "vectors.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_texture
{
	t_data		img;
	t_vec2_i	size;
}				t_texture;

/*    //CAMERA STRUCTURE\\    */
typedef struct s_camera
{
	char			id;
	t_vec3_d		pos;
	t_vec3_d		lookat;
	t_vec2_d		scene_window;
	t_vec2_d		rtn;
	double			fov;
}				t_camera;

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
	CONE,
	METAL,
	METALPLANE,
	METALSPHERE,
	METALCONE
}				t_objtype;

typedef enum e_axises
{
	aX = 0,
	aY,
	aZ
}				t_axises;

typedef struct s_ambient
{
	float			value;
	char			id;
	t_vec3_d		color;
}				t_ambient;

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
	t_point_3	pos;
	t_vec3_d	rtn;
	t_vec3_d	scl;
}				t_transform;

typedef struct s_gameobject
{
	double		mtlnss;
	double		albedo;
	t_color_3	color;
	t_transform	trs;
	t_objtype	type;
	int			defnum;
	char		*text;
	t_texture	texture;
	char		is_invisible;
}				t_gameobject;

typedef t_gameobject	t_sphere;
typedef t_gameobject	t_cylinder;
typedef t_gameobject	t_plane;
typedef t_gameobject	t_cone;

/*    //RAY STRUCTURES\\    */
typedef struct s_raydata
{
	t_vec3_d		color;
	t_vec3_d		metalcolor;
	t_vec3_d		hit_point;
	t_gameobject	*hit_ptr;
	char			hit_something;
	t_vec3_d		point_normal;
	double			sqr_distance;
	char			ismetal;
}				t_raydata;

typedef struct s_ray
{
	t_raydata		data;
	t_vec3_d		dir;
	t_tracing_mode	mode;
	t_vec3_d		source;
	double			max_sqr_len;
	char			depth;
	double			sqr_best;
}				t_ray;

/*    //ALL PURPOSE STRUCTURE\\    */
typedef struct s_window
{
	void			*mlx;
	void			*win;
	t_data			img;
	t_texture		skybox;
	t_vec2_i		size;
	t_camera		cam;
	t_ambient		ambient;
	t_list			*scene;
	int				obj_num;
	t_list			*lights;
	int				anti_aliasing;
	char			toggle_hd;
	t_gameobject	*selected;
	double			step;
	char			do_exit;
	int				num_line;
	char			**rt;
}	t_window;

/*    //FUNCTIONS\\    */
int				win_close(t_window *win);
int				manage_keys(int keypressed, t_window *win);
int				manage_mouse(int button, int x, int y, t_window *win);
void			my_image_creator(t_window *w);
void			my_mlx_pixel_put(t_data *data, int x, int y, int cl);
void			reimage(t_window *win);
t_vec3_d		create_argb(int r, int g, int b);
t_vec3_d		create_argb_s(double r, double g, double b);
int				create_trgb(int a, int r, int g, int b);
int				create_trgb_s(double a, double r, double g, double b);
int				pull_argb(t_vec3_d c, int div);
char			rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode);
t_vec3_d		skybox_calc(t_ray r, t_texture t, t_vec3_d *offset);
t_vec3_d		rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);
unsigned int	my_mlx_pixel_get(t_data data, int x, int y);
int				rft_anti_aliasing(const t_vec2_i c,
					const t_vec3_d div_temp, t_ray *r, t_window *w);
void			rft_window_cast(t_window *w);
void			my_image_creator(t_window *w);
void			v3d_rotate(t_vec3_d *v, t_axises a, double rot);
void			clean_scene_list(t_list *lst, t_window *win, char mode);

/*collisions testers*/
int				hit_cylinder(t_cylinder *c, t_ray *r, t_tracing_mode mode);
int				hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode);
int				hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode);
t_vec3_d		cylinder_normal(t_transform tr, t_vec3_d pt);

/*utils_1.c*/

t_vec3_d		rft_refract(const t_vec3_d uv, const t_vec3_d n, double t);
int				metal_manager(t_ray *r, t_gameobject *gm);

/*file color_opers.c*/
t_vec3_d		create_argb_s(double r, double g, double b);
int				create_trgb_s(double a, double r, double g, double b);
int				create_trgb(int a, int r, int g, int b);
int				pull_argb(t_vec3_d c, int div);
t_vec3_d		create_argb(int r, int g, int b);
void			reimage(t_window *win);
void			my_mlx_pixel_put(t_data *data, int x, int y, int cl);
unsigned int	my_mlx_pixel_get(t_data data, int x, int y);

/*file image_creat.c*/
int				hit_sphere(t_sphere *sphere, t_ray *r, t_tracing_mode mode);
int				hit_plane(t_plane *plane, t_ray *r, t_tracing_mode mode);
int				hit_cylinder(t_cylinder *cylinder, t_ray *r,
					t_tracing_mode mode);
int				type_sorter(t_objtype t, t_gameobject *obj,
					t_ray *r, t_tracing_mode mode);
char			rft_hitter(t_list *scene, t_ray *r, t_tracing_mode mode);
t_color_3		rft_specular(t_ray *r, t_ray *lr, t_lantern *l);
t_color_3		rft_diffuse(t_ray *r, t_ray *o, t_lantern *l);
t_vec3_d		rft_search_light(t_window *w, t_ray *r);
t_vec3_d		rft_cast(t_window *w, t_ray *r, t_tracing_mode mode);

/*file input.c*/
int				win_close(t_window *win);
int				manage_keys(int keypressed, t_window *win);
int				manage_mouse(int button, int x, int y, t_window *w);
void			rt_rotate_object(t_gameobject *o, t_axises a, double rot);

/*file palle.c*/
int				rft_anti_aliasing(const t_vec2_i c, const t_vec3_d div_temp,
					t_ray *r, t_window *w);
void			*build_pt(t_window *w, int i, int j);
void			rft_window_cast(t_window *w);
void			my_image_creator(t_window *w);

/*file utils.c*/
t_raydata		unpack_ray(void *a);
void			transform_out(t_transform t);
t_vec3_d		ray_at(t_ray *r, double t);

/*file check_rt.c*/
int				contchar(t_window *w);
char			*ft_strjoin2(char *s1, char *s2);
t_gameobject	*ft_get_text(t_gameobject *p, char **line, t_window *w,
					t_gameobject *o);

void			lol_checkmetal(t_gameobject *p, t_window *w, t_gameobject *o);

/*file read_rt.c*/
int				ft_check_file(char *scene);
int				ft_check_data(t_window *w);
void			ft_read_rt(t_window *w, char *scene);
int				ft_open_rt(t_window *w, char **av);
void			ft_initcam(t_window *w);

/*file parsing.c*/
float			tofloat(char **str);
t_vec3_d		color_parse(char **str, t_window *w, void *s);
t_vec3_d		pos_parse(char **str, t_window *w, void *s);
int				ft_line_parser(t_window *w, char *line);

/*file init.c*/
void			rft_add_gameobject_to_scene(t_window *w,
					t_gameobject *elem, char *texture);
t_list			*ft_lstnew_dup(const void *a, int size);
t_transform		new_transform(t_vec3_d p, t_vec3_d r, t_vec3_d s);
t_gameobject	*new_gameobject(t_transform tr, t_color_3 cl,
					t_objtype type, double sh);
t_gameobject	new_object1(t_transform tr, t_color_3 cl, t_objtype type);

/*file init_help.c*/
int				rft_load_scene(t_window *w);
int				initw(t_window *win);
int				loop_rt(t_window *w);
void			camera_init(t_window *win);

/*file parse_utils.c*/
int				ft_char_digit(char *str);
void			*sux_malloc(unsigned int size, t_window *w);
void			next_val(char **str);
int				my_atoi(char **str);
void			ft_comma(char **str, t_window *w, void *s);

/*file parse_utils2.c*/

char			*ft_copyadd(char *str);
void			ft_check_path(t_gameobject *s, t_window *w);
void			free_obj(t_list *scene);
int				ft_print_error(char *err, t_window *w, void *del);
int				ft_checkset(char c, char *s);

/*file parse_data.c*/
int				camera_update(t_window *w);
int				parse_res(t_window *w, char **line);
int				parse_amb(t_window *w, char **line);
int				parse_cam(t_window *w, char **line);
int				parse_light(t_window *w, char **line);

/*file parse_obj.c*/
int				parse_sphere(t_window *w, char **line);
int				parse_plane(t_window *w, char **line);
int				parse_cylinder(t_window *w, char **line);

/*checker_color.c*/
int				checker_disr_plane(t_transform tr, t_ray *r,
					t_vec3_d pt, t_vec3_d col);
char			checker_cases(double lol, t_vec3_d tempx, t_vec3_d tempy,
					t_vec3_d pt);
char			checker_disr_sphere(t_vec3_d offset, t_ray *r, t_vec3_d col);
double			modulus(double a);

#endif
