/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopeyrat <dopeyrat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:37:03 by dopeyrat          #+#    #+#             */
/*   Updated: 2023/10/16 12:56:53 by dopeyrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include "LIBFT/libft.h"
# include <math.h>
# include <mlx.h>
# include <sys/time.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_MALLOC 2
# define EXIT_OPEN 3
# define EXIT_READ 4
# define EXIT_EXTENSION 5
# define EXIT_MAP_ERROR 6
# define EXIT_MISS_ID 7
# define EXIT_DUP_ID 8
# define EXIT_COR_ID 9
# define EXIT_WALL_ERROR 10
# define EXIT_MISS_PLAYER 11
# define EXIT_DUP_PLAYER 12
# define EXIT_MLX_ERR 13
# define EXIT_TEXTURE_ERR 14

# define UP 13
# define LEFT 0
# define DOWN 1
# define RIGHT 2
# define SHIFT 257
# define E 14
# define ROTATE_RIGHT 124
# define ROTATE_LEFT 123

# define PI 3.14159265
# define HORIZONTAL 1280
# define VERTICAL 720
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
//V_FOV = PI / 3
# define V_FOV 1.04719755
//H_FOV = 2 * arctan(tan(V_FOV / 2) * (HORIZONTAL / VERTICAL))
# define H_FOV 1.59685138
//1000 microsec / FPS
# define FRAME_INTERVAL 8.33333333

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_texture
{
	void	*mlx_img;
	int		width;
	int		height;

	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_texture;

typedef struct s_player
{
	double		x;
	double		y;
	double		a;
	double		x_off;
	double		y_off;

	double		planex;
	double		planey;

	double		camerax;

	double		raydirx;
	double		raydiry;

	int			mapx;
	int			mapy;

	double		sidedistx;
	double		sidedisty;

	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;

	int			stepx;
	int			stepy;

	int			lineheight;
	int			drawstart;
	int			drawend;

	int			side;
	int			hit;

	double		wallx;

	t_texture	*texture;

	int			texx;
	int			texy;

	double		step;
	double		texpos;
}				t_player;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

typedef struct s_ray
{
	double	distance;
	char	wall_face;
	double	wall_h;
}				t_ray;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;

	t_img		mini1;
	t_img		mini2;

	t_img		img1;
	t_img		img2;

	int			index;

	t_texture	no;
	t_texture	so;
	t_texture	ea;
	t_texture	we;
}				t_mlx;

typedef struct s_cube
{
	t_player		*p;
	char			**map;
	int				m_y;
	int				m_x;
	char			*n_t;
	char			*s_t;
	char			*w_t;
	char			*e_t;
	unsigned int	f;
	unsigned int	c;
	int				f_f;
	int				c_f;

	t_mlx			mlx;

	int				key_a;
	int				key_w;
	int				key_s;
	int				key_d;
	double			key_shift;

	long long		last_frame;
	int				x;
	int				y;

	int				epilepsy;
	unsigned int	e_counter;
}				t_cube;

int				ft_exit(t_cube *data, int status);
void			init_mlx(t_cube *data);

/* ---------- FREE ---------- */

t_cube			*free_cub3d(t_cube *data);
void			free_cube_map(char **map);

/* ---------- INIT ---------- */

void			check_walls(t_cube *data);
void			set_player(t_cube *data);
int				check_args(int ac, char **argv);
t_cube			*init_data(int fd);
int				is_map_id(char *str);
int				all_id_found(t_cube *data);
int				add_map_id(char *str, t_cube *data, int fd, int i);
int				re_malloc_map(char *str, t_cube *data, int fd);
void			check_map(t_cube *data);
char			**copy_map(t_cube *data);

/* ---------- UTILS ---------- */

int				is_empty_str(char *str);
int				create_trgb(int t, int r, int g, int b);
void			my_mlx_pixel_put(t_img *img, int x, int y, int colour);
long long		get_time(void);
long long		time_diff(long long past, long long pres);
unsigned int	generate_cf(unsigned int colour, t_cube *data);
void			put_texture(t_img *img, t_cube *data, int i, int j);

/* ------- MLX  EVENTS ------- */

int				keypress(int keycode, t_cube *data);
int				keyrelease(int keycode, t_cube *data);
int				mouse_click(int keycode, int x, int y, t_cube *data);
int				mouse_move(int x, int y, t_cube *data);
int				window_closed(t_cube *data);
int				no_input(t_cube *data);

/* ---------- RENDER ---------- */

void			render(t_cube *data);
//void			draw_line(t_img *mini, int x1, int y1, int x2, int y2);
void			cast_rays(t_cube *data, t_img *img, t_player *p);
void			render_minimap(t_cube *data, t_img *mini);

/* ---------- COLOURS ---------- */

unsigned int	gen_rgb(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);
unsigned int	gen_rbg(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);
unsigned int	gen_grb(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);
unsigned int	gen_gbr(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);
unsigned int	gen_brg(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);
unsigned int	gen_bgr(t_cube *data, unsigned int high,
					unsigned int mid, unsigned int low);

#endif
