/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commit_pixels.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:11:33 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/15 12:11:35 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	are_in(t_all *all, int i, int j, char flag)
{
	t_dot	*a;
	t_dot	*b;

	a = &all->matrix[i][j];
	if (flag == 'i')
	{
		b = &all->matrix[i + 1][j];
		if ((a->x > 1000 || a->x < 0 || a->y > 1000 || a->y < 0)
			&& (b->x > 1000 || b->x < 0 || b->y > 1000 || b->y < 0))
			return (0);
		else
			return (1);
	}
	if (flag == 'j')
	{
		b = &all->matrix[i][j + 1];
		if ((a->x > 1000 || a->x < 0 || a->y > 1000 || a->y < 0)
			&& (b->x > 1000 || b->x < 0 || b->y > 1000 || b->y < 0))
			return (0);
		else
			return (1);
	}
	return (1);
}

void	commit_speck(t_img *img, int x, int y, int color)
{
	int		center_x;
	int		center_y;
	int		delta;
	char	*pixel;

	center_x = x;
	center_y = y;
	x = center_x - 2;
	while (x <= center_x + 2)
	{
		y = center_y - 2;
		while (y <= center_y + 2)
		{
			if (y >= 0 && y < 1000 && x >= 0 && x < 1000)
			{
				delta = (y * img->ll + x * (img->bpp / 8));
				pixel = img->addr + delta;
				*(unsigned int *)pixel = color;
			}
			y++;
		}
		x++;
	}
}

void	commit_j_line(t_all *all, int i, int j)
{
	float	xy[2];
	t_dot	*a;
	t_dot	*b;

	a = &all->matrix[i][j];
	b = &all->matrix[i][j + 1];
	xy[0] = a->x;
	xy[1] = a->y;
	while (!((xy[0] > b->x - 1) && (xy[0] <= b->x + 1) && (xy[1] > b->y - 1)
			&& (xy[1] <= b->y + 1)) || (xy[0] == a->x && xy[1] == a->y))
	{
		commit_speck(all->img, (int) xy[0], (int) xy[1], obtain_color(
				color_ratio(a, b, xy), a->cor, b->cor));
		if (fabsf(b->x - a->x) > fabsf(b->y - a->y))
			xy[0] += 1 - (2 * ((b->x - a->x) < 0));
		if (fabsf(b->x - a->x) > fabsf(b->y - a->y))
			xy[1] += 1 * (b->y - a->y) / fabsf(b->x - a->x);
		if (fabsf(b->x - a->x) <= fabsf(b->y - a->y))
			xy[0] += 1 * (b->x - a->x) / fabsf(b->y - a->y);
		if (fabsf(b->x - a->x) <= fabsf(b->y - a->y))
			xy[1] += 1 - (2 * ((b->y - a->y) < 0));
		if ((xy[0] > b->x + 1000 && (b->x > a->x)) || (xy[0] < b->x - 1000 
				&& (b->x <= a->x)) || (b->x == a->x && b->y == a->y))
			break ;
	}
}

void	commit_i_line(t_all *all, int i, int j)
{
	float	xy[2];
	t_dot	*a;
	t_dot	*b;

	a = &all->matrix[i][j];
	b = &all->matrix[i + 1][j];
	xy[0] = a->x;
	xy[1] = a->y;
	while (!((xy[0] > b->x - 1) && (xy[0] <= b->x + 1) && (xy[1] > b->y - 1)
			&& (xy[1] <= b->y + 1)) || (xy[0] == a->x && xy[1] == a->y))
	{
		commit_speck(all->img, (int) xy[0], (int) xy[1], obtain_color(
				color_ratio(a, b, xy), a->cor, b->cor));
		if (fabsf(b->x - a->x) > fabsf(b->y - a->y))
			xy[0] += 1 - (2 * ((b->x - a->x) < 0));
		if (fabsf(b->x - a->x) > fabsf(b->y - a->y))
			xy[1] += 1 * (b->y - a->y) / fabsf(b->x - a->x);
		if (fabsf(b->x - a->x) <= fabsf(b->y - a->y))
			xy[0] += 1 * (b->x - a->x) / fabsf(b->y - a->y);
		if (fabsf(b->x - a->x) <= fabsf(b->y - a->y))
			xy[1] += 1 - (2 * ((b->y - a->y) < 0));
		if ((xy[0] > b->x + 1000 && (b->x > a->x)) || (xy[0] < b->x - 1000 
				&& (b->x <= a->x)) || (b->x == a->x && b->y == a->y))
			break ;
	}
}

void	commit_lines(t_all *all, int start_i, int start_j)
{
	int	i;
	int	j;
	int	di;
	int	dj;

	di = 1;
	if (start_i)
		di = -1;
	dj = 1;
	if (start_j)
		dj = -1;
	i = start_i;
	while (i < all->ly && i >= 0)
	{
		j = start_j;
		while (j < all->lx && j >= 0)
		{
			if (j != all->lx - 1 && are_in(all, i, j, 'j'))
				commit_j_line(all, i, j);
			if (i != all->ly - 1 && are_in(all, i, j, 'i'))
				commit_i_line(all, i, j);
			j += dj;
		}
		i += di;
	}
}
