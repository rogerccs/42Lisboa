/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:21:10 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/20 14:21:11 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	malloc_exit(void)
{
	write(2, "Not enough heap memory\n", 23);
	exit(0);
}

void	invalid_fd_exit(void)
{
	write(2, "Invalid filename\n", 17);
	exit(0);
}

int	clean_exit(t_all *all)
{
	int	i;

	if (all->img->img)
		mlx_destroy_image(all->mlx->mlx, all->img->img);
	if (all->mlx->win)
		mlx_destroy_window(all->mlx->mlx, all->mlx->win);
	if (all->mlx->mlx)
		mlx_destroy_display(all->mlx->mlx);
	if (all->mlx->mlx)
		free(all->mlx->mlx);
	i = 0;
	if (all->matrix)
	{
		while (all->matrix[i])
			free(all->matrix[i++]);
		free(all->matrix);
	}
	exit(0);
	return (0);
}
