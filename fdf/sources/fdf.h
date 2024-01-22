/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:00:39 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/13 15:00:41 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>
# include "../mlx/mlx.h"

# define PI 3.1415

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_img;

typedef struct s_dot
{
	int		z;
	int		cor;
	float	x;
	float	y;
}	t_dot;

typedef struct s_all
{
	t_mlx	*mlx;
	t_img	*img;
	t_dot	**matrix;
	int		lx;
	int		ly;
	int		dx;
	int		dy;
	int		dz;
	int		xpos;
	int		ypos;
	int		zmin;
	int		zmax;
	int		angle;
	float	ux;
	float	uy;
	float	uz;
	float	camx;
	float	camy;
	float	camz;
	double	cam_ux[3];
	double	cam_uy[3];
	double	cam_uz[3];
	char	proj;
	char	key_a;
	char	key_w;
	char	key_d;
	char	key_s;
	char	key_q;
	char	key_e;
	char	key_r;
	char	key_i;
	char	key_p;
	char	key_j;
	char	key_k;
	char	key_n;
	char	key_m;
	char	key_left;
	char	key_up;
	char	key_right;
	char	key_down;
	char	key_shift;
	char	key_ctrl;
}	t_all;

int		render(t_all *all);
int		clean_exit(t_all *all);
int		ft_atoi(const char *nptr);
int		ft_htoi(const char *nptr);
int		ft_printf(const char *str, ...);
int		key_pressed(int keycode, t_all *all);
int		key_released(int keycode, t_all *all);
int		mouse_pressed(int buttoncode, int x, int y, t_all *all);
int		obtain_color(float ratio, int color_a, int color_b);
char	*get_next_line(int fd);
char	are_in(t_all *all, int i, int j, char flag);
void	parallel(t_all *all);
void	fildefer(t_all *all);
void	isometric(t_all *all);
void	invalid_fd_exit(void);
void	malloc_exit(void);
void	prepare_parallel(t_all *all);
void	prepare_isometric(t_all *all);
void	obtain_dimensions(t_all *all);
void	cam_orbit_xy(t_all *all, float ome);
void	cam_orbit_yz(t_all *all, float tta);
void	commit_j_line(t_all *all, int i, int j);
void	commit_i_line(t_all *all, int i, int j);
void	*ft_memset(void *s, int c, size_t n);
void	cam_rotate_yaw(t_all *all, float phi);
void	cam_rotate_roll(t_all *all, float ome);
void	cam_rotate_pitch(t_all *all, float tta);
void	translate(t_all *all, double *u, char flag);
void	update_positioning(t_all *all, char flag);
void	commit_pixels_parallel(t_all *all);
void	commit_lines(t_all *all, int start_i, int start_j);
void	zero_coordinates(t_all *all);
void	ninety_coordinates(t_all *all);
void	one_eighty_coordinates(t_all *all);
void	two_seventy_coordinates(t_all *all);
void	key_pressed_parallel(int keycode, t_all *all);
void	key_pressed_isometric(int keycode, t_all *all);
void	colour_dots(t_all *all, int cormin, int cormax);
void	mouse_action_parallel(int buttoncode, int x, int y, t_all *all);
void	mouse_action_isometric(int buttoncode, int x, int y, t_all *all);
float	color_ratio(t_dot *a, t_dot *b, float xy[2]);

#endif
