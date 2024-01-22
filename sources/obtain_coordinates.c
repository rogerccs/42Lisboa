/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obtain_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 08:48:02 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/17 08:48:03 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zero_coordinates(t_all *all)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;
	t_dot	*dot;

	xpos = all->xpos + all->dx;
	ypos = all->ypos + all->dy;
	i = 0;
	while (i < all->ly)
	{
		j = 0;
		while (j < all->lx)
		{
			dot = &all->matrix[i][j];
			dot->x = xpos + (j - i) * all->ux;
			dot->y = ypos + (i + j) * all->uy - dot->z * all->uz;
			j++;
		}
		i++;
	}
}

void	ninety_coordinates(t_all *all)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;
	t_dot	*dot;

	xpos = all->xpos + all->dx;
	ypos = all->ypos + all->dy;
	i = 0;
	while (i < all->ly)
	{
		j = 0;
		while (j < all->lx)
		{
			dot = &all->matrix[i][j];
			dot->x = xpos + (-j - i) * all->ux;
			dot->y = ypos + (-i + j) * all->uy - dot->z * all->uz;
			j++;
		}
		i++;
	}
}

void	one_eighty_coordinates(t_all *all)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;
	t_dot	*dot;

	xpos = all->xpos + all->dx;
	ypos = all->ypos + all->dy;
	i = 0;
	while (i < all->ly)
	{
		j = 0;
		while (j < all->lx)
		{
			dot = &all->matrix[i][j];
			dot->x = xpos + (-j + i) * all->ux;
			dot->y = ypos + (-i - j) * all->uy - dot->z * all->uz;
			j++;
		}
		i++;
	}
}

void	two_seventy_coordinates(t_all *all)
{
	int		i;
	int		j;
	int		xpos;
	int		ypos;
	t_dot	*dot;

	xpos = all->xpos + all->dx;
	ypos = all->ypos + all->dy;
	i = 0;
	while (i < all->ly)
	{
		j = 0;
		while (j < all->lx)
		{
			dot = &all->matrix[i][j];
			dot->x = xpos + (j + i) * all->ux;
			dot->y = ypos + (i - j) * all->uy - dot->z * all->uz;
			j++;
		}
		i++;
	}
}
