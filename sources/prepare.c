/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:49:29 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/24 17:49:31 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_positioning(t_all *all, char flag)
{
	if (flag == 'R')
		all->angle += 90;
	all->xpos = (all->ly) * cos(PI * 0.1667) 
		/ (all->lx + all->ly) / cos(PI * 0.1667) * 1000;
	all->ypos = (1000 - 1000 * (all->lx + all->ly) * sin(PI * 0.1667)
			/ (all->lx + all->ly) / cos(PI * 0.1667)) / 2;
	if (all->angle % 360 == 90)
	{
		all->xpos += (all->lx - 1) * all->ux;
		all->ypos += (all->ly - 1) * all->uy;
	}
	else if (all->angle % 360 == 180)
	{
		all->xpos += (all->lx - all->ly) * all->ux;
		all->ypos += (all->lx + all->ly - 2) * all->uy;
	}
	else if (all->angle % 360 == 270)
	{
		all->xpos -= (all->ly - 1) * all->ux;
		all->ypos += (all->lx - 1) * all->uy;
	}
}

void	prepare_isometric(t_all *all)
{
	all->proj = 'I';
	all->dx = 0;
	all->dy = 0;
	all->dz = 0;
	all->angle = 0;
	obtain_dimensions(all);
}

void	prepare_parallel(t_all *all)
{
	all->proj = 'P';
	all->camx = 0;
	all->camy = all->ly + 10;
	all->camz = 10;
	all->cam_ux[0] = 1;
	all->cam_ux[1] = 0;
	all->cam_ux[2] = 0;
	all->cam_uy[0] = 0;
	all->cam_uy[1] = 0;
	all->cam_uy[2] = -1;
	all->cam_uz[0] = 0;
	all->cam_uz[1] = -1;
	all->cam_uz[2] = 0;
}
