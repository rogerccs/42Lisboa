/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:41:36 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/27 17:41:37 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cam_rotate_z(t_all *all, float ome)
{
	double	newus[6];
	double	*ux;
	double	*uy;
	double	*uz;

	ux = all->cam_ux;
	uy = all->cam_uy;
	uz = all->cam_uz;
	newus[0] = cos(ome) * ux[0] - sin(ome) * ux[1];
	newus[1] = sin(ome) * ux[0] + cos(ome) * ux[1];
	newus[2] = cos(ome) * uy[0] - sin(ome) * uy[1];
	newus[3] = sin(ome) * uy[0] + cos(ome) * uy[1];
	newus[4] = cos(ome) * uz[0] - sin(ome) * uz[1];
	newus[5] = sin(ome) * uz[0] + cos(ome) * uz[1];
	ux[0] = newus[0];
	ux[1] = newus[1];
	uy[0] = newus[2];
	uy[1] = newus[3];
	uz[0] = newus[4];
	uz[1] = newus[5];
}

void	cam_rotate_x(t_all *all, float tta)
{
	double	newus[6];
	double	*ux;
	double	*uy;
	double	*uz;

	ux = all->cam_ux;
	uy = all->cam_uy;
	uz = all->cam_uz;
	newus[0] = cos(tta) * ux[1] - sin(tta) * ux[2];
	newus[1] = sin(tta) * ux[1] + cos(tta) * ux[2];
	newus[2] = cos(tta) * uy[1] - sin(tta) * uy[2];
	newus[3] = sin(tta) * uy[1] + cos(tta) * uy[2];
	newus[4] = cos(tta) * uz[1] - sin(tta) * uz[2];
	newus[5] = sin(tta) * uz[1] + cos(tta) * uz[2];
	ux[1] = newus[0];
	ux[2] = newus[1];
	uy[1] = newus[2];
	uy[2] = newus[3];
	uz[1] = newus[4];
	uz[2] = newus[5];
}

void	cam_orbit_xy(t_all *all, float ome)
{
	float	rxy;
	float	ome_zero;

	rxy = sqrt(pow(all->camx - all->lx / 2, 2)
			+ pow(all->camy - all->ly / 2, 2));
	ome_zero = atan2((all->camy - all->ly / 2), (all->camx - all->lx / 2));
	all->camx = all->lx / 2 + rxy * cos(ome_zero + ome);
	all->camy = all->ly / 2 + rxy * sin(ome_zero + ome);
	cam_rotate_z(all, ome);
}

void	cam_orbit_yz(t_all *all, float tta)
{
	float	ryz;
	float	tta_zero;

	ryz = sqrt(pow(all->camz, 2) + pow(all->camy - all->ly / 2, 2));
	tta_zero = atan2(all->camz, all->camy - all->ly / 2);
	all->camy = all->ly / 2 + ryz * cos(tta_zero + tta);
	all->camz = ryz * sin(tta_zero + tta);
	cam_rotate_x(all, tta);
}
