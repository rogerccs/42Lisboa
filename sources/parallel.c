/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:24:36 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/21 13:24:38 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	obtain_parallel_coordinates(t_all *all, float h)
{
	int		i;
	int		j;
	float	closure;
	t_dot	*dot;

	i = -1;
	while (++i < all->ly)
	{
		j = -1;
		while (++j < all->lx)
		{
			dot = &all->matrix[i][j];
			closure = ((j - all->camx) * all->cam_uz[0] 
					+ (i - all->camy) * all->cam_uz[1] 
					+ (dot->z / 10 - all->camz) * all->cam_uz[2]) / 1000;
			if (closure <= 0)
				closure = 0.00001;
			dot->x = 500 + ((j - all->camx) * all->cam_ux[0]
					+ (i - all->camy) * all->cam_ux[1]
					+ (dot->z / h - all->camz) * all->cam_ux[2]) / closure;
			dot->y = 500 + ((j - all->camx) * all->cam_uy[0] 
					+ (i - all->camy) * all->cam_uy[1]
					+ (dot->z / h - all->camz) * all->cam_uy[2]) / closure;
		}
	}
}

void	commit_quadrant(t_all *all, int dj, int di)
{
	int		i;
	int		j;

	i = all->ly - 1;
	if (di > 0)
		i = 0;
	while (i < all->ly && i >= 0)
	{
		j = all->lx - 1;
		if (dj > 0)
			j = 0;
		while (j < all->lx && j >= 0)
		{
			if (((dj > 0 && j <= all->camx) || (dj < 0 && j > all->camx))
				&& ((di > 0 && i <= all->camy) || (di < 0 && i > all->camy))
				&& j != all->lx - 1 && are_in(all, i, j, 'j'))
				commit_j_line(all, i, j);
			if (((dj > 0 && j <= all->camx) || (dj < 0 && j > all->camx))
				&& ((di > 0 && i <= all->camy) || (di < 0 && i > all->camy))
				&& i != all->ly - 1 && are_in(all, i, j, 'i'))
				commit_i_line(all, i, j);
			j += dj;
		}
		i += di;
	}
}

void	commit_pixels_parallel(t_all *all)
{
	int		dirx;
	int		diry;

	dirx = all->cam_uz[0];
	diry = all->cam_uz[1];
	commit_quadrant(all, 1 - 2 * (dirx >= 0), 1 - 2 * (diry < 0));
	commit_quadrant(all, 1 - 2 * (dirx < 0), 1 - 2 * (diry >= 0));
	commit_quadrant(all, 1 - 2 * (dirx < 0), 1 - 2 * (diry < 0));
	commit_quadrant(all, 1 - 2 * (dirx >= 0), 1 - 2 * (diry >= 0));
}

void	parallel(t_all *all)
{
	t_mlx	*mlx;
	t_img	*img;

	mlx = all->mlx;
	img = all->img;
	if (img->img)
		mlx_destroy_image(mlx->mlx, img->img);
	img->img = mlx_new_image(mlx->mlx, 1000, 1000);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	obtain_parallel_coordinates(all, fmax(abs(all->zmin), abs(all->zmax)) / 8);
	commit_pixels_parallel(all);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}
