/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fildefer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:02:25 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/14 18:02:26 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	obtain_min_max(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	all->zmin = INT_MAX;
	all->zmax = INT_MIN;
	while (i < all->ly)
	{
		j = 0;
		while (j < all->lx)
		{
			if (all->matrix[i][j].z > all->zmax)
				all->zmax = all->matrix[i][j].z;
			if (all->matrix[i][j].z < all->zmin)
				all->zmin = all->matrix[i][j].z;
			j++;
		}
		i++;
	}
}

void	obtain_dimensions(t_all *all)
{
	float	x_size;
	float	y_size;
	float	proportion;

	x_size = (all->lx + all->ly) * cos(PI * 0.1667);
	y_size = (all->lx + all->ly) * sin(PI * 0.1667);
	proportion = y_size / x_size;
	all->xpos = (all->ly) * cos(PI * 0.1667) / x_size * 1000;
	all->ypos = (1000 - 1000 * proportion) / 2;
	all->ux = 1000. / (all->lx + all->ly);
	all->uy = (1000. * proportion) / (all->lx + all->ly);
	all->uz = (1000. * proportion) / (all->lx + all->ly) * 10
		/ fmax(abs(all->zmin), abs(all->zmax));
}

void	set_keys_to_zero(t_all *all)
{
	all->key_a = 0;
	all->key_w = 0;
	all->key_d = 0;
	all->key_s = 0;
	all->key_q = 0;
	all->key_e = 0;
	all->key_r = 0;
	all->key_i = 0;
	all->key_p = 0;
	all->key_j = 0;
	all->key_k = 0;
	all->key_n = 0;
	all->key_m = 0;
	all->key_left = 0;
	all->key_up = 0;
	all->key_right = 0;
	all->key_down = 0;
	all->key_shift = 0;
	all->key_ctrl = 0;
}

void	fildefer(t_all *all)
{
	all->dx = 0;
	all->dy = 0;
	all->dz = 0;
	all->proj = 'I';
	all->angle = 0;
	all->img->img = 0;
	obtain_min_max(all);
	if (!(all->zmin || all->zmax))
		all->zmax = 1;
	obtain_dimensions(all);
	set_keys_to_zero(all);
	colour_dots(all, 0xb67923, 0x44e866);
	isometric(all);
}
