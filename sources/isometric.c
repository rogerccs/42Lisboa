/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:50:30 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/17 08:50:31 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	obtain_coordinates(t_all *all)
{
	if (all->angle % 360 == 0)
		zero_coordinates(all);
	if (all->angle % 360 == 90)
		ninety_coordinates(all);
	if (all->angle % 360 == 180)
		one_eighty_coordinates(all);
	if (all->angle % 360 == 270)
		two_seventy_coordinates(all);
}

void	commit_pixels(t_all *all)
{
	if (all->angle % 360 == 0)
		commit_lines(all, 0, 0);
	if (all->angle % 360 == 90)
		commit_lines(all, all->ly - 1, 0);
	if (all->angle % 360 == 180)
		commit_lines(all, all->ly - 1, all->lx - 1);
	if (all->angle % 360 == 270)
		commit_lines(all, 0, all->lx - 1);
}

void	isometric(t_all *all)
{
	t_mlx	*mlx;
	t_img	*img;

	mlx = all->mlx;
	img = all->img;
	if (img->img)
		mlx_destroy_image(mlx->mlx, img->img);
	img->img = mlx_new_image(mlx->mlx, 1000, 1000);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
	obtain_coordinates(all);
	commit_pixels(all);
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->img, 0, 0);
}
