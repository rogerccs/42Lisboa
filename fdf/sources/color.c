/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:50:40 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/15 11:50:42 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	color_ratio(t_dot *a, t_dot *b, float xy[2])
{
	if (a->x == b->x && a->y == b->y)
		return (0);
	else if (a->x == b->x)
		return ((xy[1] - a->y) / (b->y - a->y));
	else
		return ((xy[0] - a->x) / (b->x - a->x));
}

int	obtain_color(float ratio, int color_a, int color_b)
{
	int	delta_r;
	int	delta_g;
	int	delta_b;
	int	color;

	if (ratio > 1)
		ratio = 1;
	delta_r = ((color_b & 0xFF0000) - (color_a & 0xFF0000)) >> 16;
	delta_g = ((color_b & 0x00FF00) - (color_a & 0x00FF00)) >> 8;
	delta_b = (color_b & 0x0000FF) - (color_a & 0x0000FF);
	color = ((((color_a & 0xFF0000) >> 16) + (int)(ratio * delta_r)) << 16)
		+ ((((color_a & 0x00FF00) >> 8) + (int)(ratio * delta_g)) << 8)
		+ ((color_a & 0x0000FF) + ratio * delta_b);
	return (color);
}

void	colour_dots(t_all *all, int cormin, int cormax)
{
	int		i;
	int		j;
	int		color;
	t_dot	*dot;
	float	ratio;

	i = -1;
	while (++i < all->ly)
	{
		j = -1;
		while (++j < all->lx)
		{
			dot = &all->matrix[i][j];
			ratio = (float)(dot->z - all->zmin) 
				/ (all->zmax - all->zmin);
			if (all->zmax == all->zmin)
				ratio = 0;
			if (!dot->cor)
			{
				color = obtain_color(ratio, cormin, cormax);
				dot->cor = color;
			}
		}
	}
}
