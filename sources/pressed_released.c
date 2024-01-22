/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:59:12 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/16 12:59:13 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_pressed_two(int keycode, t_all *all)
{
	if (keycode == 'j')
		all->key_j = 1;
	if (keycode == 'k')
		all->key_k = 1;
	if (keycode == 65361)
		all->key_left = 1;
	if (keycode == 65362)
		all->key_up = 1;
	if (keycode == 65363)
		all->key_right = 1;
	if (keycode == 65364)
		all->key_down = 1;
	if (keycode == 65505)
		all->key_shift = 1;
	if (keycode == 65507)
		all->key_ctrl = 1;
	if (keycode == 65307)
		clean_exit(all);
}

int	key_pressed(int keycode, t_all *all)
{
	if (keycode == 'a')
		all->key_a = 1;
	if (keycode == 'w')
		all->key_w = 1;
	if (keycode == 'd')
		all->key_d = 1;
	if (keycode == 's')
		all->key_s = 1;
	if (keycode == 'q')
		all->key_q = 1;
	if (keycode == 'e')
		all->key_e = 1;
	if (keycode == 'r' && all->proj == 'I')
		update_positioning(all, 'R');
	if (keycode == 'i')
		all->key_i = 1;
	if (keycode == 'p')
		all->key_p = 1;
	if (keycode == 'n')
		all->key_n = 1;
	if (keycode == 'm')
		all->key_m = 1;
	key_pressed_two(keycode, all);
	return (0);
}

void	key_released_two(int keycode, t_all *all)
{
	if (keycode == 'j')
		all->key_j = 0;
	if (keycode == 'k')
		all->key_k = 0;
	if (keycode == 65361)
		all->key_left = 0;
	if (keycode == 65362)
		all->key_up = 0;
	if (keycode == 65363)
		all->key_right = 0;
	if (keycode == 65364)
		all->key_down = 0;
	if (keycode == 65505)
		all->key_shift = 0;
	if (keycode == 65507)
		all->key_ctrl = 0;
}

int	key_released(int keycode, t_all *all)
{
	if (keycode == 'a')
		all->key_a = 0;
	if (keycode == 'w')
		all->key_w = 0;
	if (keycode == 'd')
		all->key_d = 0;
	if (keycode == 's')
		all->key_s = 0;
	if (keycode == 'q')
		all->key_q = 0;
	if (keycode == 'e')
		all->key_e = 0;
	if (keycode == 'r')
		all->key_r = 0;
	if (keycode == 'i')
		all->key_i = 0;
	if (keycode == 'p')
		all->key_p = 0;
	if (keycode == 'n')
		all->key_n = 0;
	if (keycode == 'm')
		all->key_m = 0;
	key_released_two(keycode, all);
	return (0);
}

int	mouse_pressed(int buttoncode, int x, int y, t_all *all)
{
	if (all->proj == 'I' && buttoncode == 4)
	{
		all->ux *= 1.1;
		all->uy *= 1.1;
		all->uz *= 1.1;
		all->dx = all->dx * 1.1 - (x - 500) / 5;
		all->dy = (all->dy - 26.40) * 1.1 - (y - 500) / 5;
		update_positioning(all, 0);
	}
	else if (all->proj == 'I' && buttoncode == 5)
	{
		all->ux /= 1.1;
		all->uy /= 1.1;
		all->uz /= 1.1;
		all->dx = all->dx / 1.1;
		all->dy = all->dy / 1.1 + 26.40;
		update_positioning(all, 0);
	}
	else if (all->proj == 'P' && buttoncode == 4)
		translate(all, all->cam_uz, '+');
	else if (all->proj == 'P' && buttoncode == 5)
		translate(all, all->cam_uz, '-');
	return (0);
}
