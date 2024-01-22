/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:14:58 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/24 17:14:59 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_parallel(t_all *all, float o)
{
	if (all->key_a)
		translate(all, all->cam_ux, '-');
	if (all->key_w)
		translate(all, all->cam_uz, '+');
	if (all->key_d)
		translate(all, all->cam_ux, '+');
	if (all->key_s)
		translate(all, all->cam_uz, '-');
	if (all->key_q)
		translate(all, all->cam_uy, '-');
	if (all->key_e)
		translate(all, all->cam_uy, '+');
	if (all->key_left || all->key_right)
		cam_rotate_yaw(all, (-o + 2 * o * all->key_left) * PI / 180);
	if (all->key_up || all->key_down)
		cam_rotate_pitch(all, (-o + 2 * o * all->key_down) * PI / 180);
	if (all->key_shift || all->key_ctrl)
		cam_rotate_roll(all, (-o + 2 * o * all->key_shift) * PI / 180);
	if (all->key_n || all->key_m)
		cam_orbit_xy(all, (-o + 2 * o * all->key_n) * PI / 180);
	if (all->key_j || all->key_k)
		cam_orbit_yz(all, (-o + 2 * o * all->key_j) * PI / 180);
	if (all->key_i)
		prepare_isometric(all);
}

void	update_isometric(t_all *all)
{
	if (all->key_a || all->key_left)
		(all->dx) += 10;
	if (all->key_w || all->key_up)
		(all->dy) += 10;
	if (all->key_d || all->key_right)
		(all->dx) -= 10;
	if (all->key_s || all->key_down)
		(all->dy) -= 10;
	if (all->key_p)
		prepare_parallel(all);
}

int	render(t_all *all)
{
	float	dangle;

	dangle = sqrt(all->lx + all->ly) / 15.; 
	if (all->proj == 'I')
	{
		update_isometric(all);
		isometric(all);
	}
	else if (all->proj == 'P')
	{
		update_parallel(all, dangle);
		parallel(all); 
	}
	return (0);
}
