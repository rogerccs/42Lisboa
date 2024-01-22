/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:03:26 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/23 12:03:28 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate(t_all *all, double *u, char flag)
{
	if (flag == '+')
	{
		all->camx += u[0] / 100 * (all->lx + all->ly) / 2;
		all->camy += u[1] / 100 * (all->lx + all->ly) / 2;
		all->camz += u[2] / 100 * (all->lx + all->ly) / 2;
	}
	if (flag == '-')
	{
		all->camx -= u[0] / 100 * (all->lx + all->ly) / 2;
		all->camy -= u[1] / 100 * (all->lx + all->ly) / 2;
		all->camz -= u[2] / 100 * (all->lx + all->ly) / 2;
	}
}

void	matrix_vector_multiplication(double m[3][3], double v[3])
{
	double	u[3];

	u[0] = v[0];
	u[1] = v[1];
	u[2] = v[2];
	v[0] = m[0][0] * u[0] + m[0][1] * u[1] + m[0][2] * u[2];
	v[1] = m[1][0] * u[0] + m[1][1] * u[1] + m[1][2] * u[2];
	v[2] = m[2][0] * u[0] + m[2][1] * u[1] + m[2][2] * u[2];
}

void	cam_rotate_yaw(t_all *all, float phi)
{
	double	*ux;
	double	*uy;
	double	*uz;
	double	rmatrix[3][3];

	ux = all->cam_ux;
	uy = all->cam_uy;
	uz = all->cam_uz;
	rmatrix[0][0] = cos(phi) + uy[0] * uy[0] * (1 - cos(phi));
	rmatrix[0][1] = uy[0] * uy[1] * (1 - cos(phi)) - uy[2] * sin(phi);
	rmatrix[0][2] = uy[0] * uy[2] * (1 - cos(phi)) + uy[1] * sin(phi);
	rmatrix[1][0] = uy[0] * uy[1] * (1 - cos(phi)) + uy[2] * sin(phi);
	rmatrix[1][1] = cos(phi) + uy[1] * uy[1] * (1 - cos(phi));
	rmatrix[1][2] = uy[1] * uy[2] * (1 - cos(phi)) - uy[0] * sin(phi);
	rmatrix[2][0] = uy[0] * uy[2] * (1 - cos(phi)) - uy[1] * sin(phi);
	rmatrix[2][1] = uy[1] * uy[2] * (1 - cos(phi)) + uy[0] * sin(phi);
	rmatrix[2][2] = cos(phi) + uy[2] * uy[2] * (1 - cos(phi));
	matrix_vector_multiplication(rmatrix, ux);
	matrix_vector_multiplication(rmatrix, uz);
}

void	cam_rotate_pitch(t_all *all, float tta)
{
	double	*ux;
	double	*uy;
	double	*uz;
	double	rmatrix[3][3];

	ux = all->cam_ux;
	uy = all->cam_uy;
	uz = all->cam_uz;
	rmatrix[0][0] = cos(tta) + ux[0] * ux[0] * (1 - cos(tta));
	rmatrix[0][1] = ux[0] * ux[1] * (1 - cos(tta)) - ux[2] * sin(tta);
	rmatrix[0][2] = ux[0] * ux[2] * (1 - cos(tta)) + ux[1] * sin(tta);
	rmatrix[1][0] = ux[0] * ux[1] * (1 - cos(tta)) + ux[2] * sin(tta);
	rmatrix[1][1] = cos(tta) + ux[1] * ux[1] * (1 - cos(tta));
	rmatrix[1][2] = ux[1] * ux[2] * (1 - cos(tta)) - ux[0] * sin(tta);
	rmatrix[2][0] = ux[0] * ux[2] * (1 - cos(tta)) - ux[1] * sin(tta);
	rmatrix[2][1] = ux[1] * ux[2] * (1 - cos(tta)) + ux[0] * sin(tta);
	rmatrix[2][2] = cos(tta) + ux[2] * ux[2] * (1 - cos(tta));
	matrix_vector_multiplication(rmatrix, uy);
	matrix_vector_multiplication(rmatrix, uz);
}

void	cam_rotate_roll(t_all *all, float ome)
{
	double	*ux;
	double	*uy;
	double	*uz;
	double	rmatrix[3][3];

	ux = all->cam_ux;
	uy = all->cam_uy;
	uz = all->cam_uz;
	rmatrix[0][0] = cos(ome) + uz[0] * uz[0] * (1 - cos(ome));
	rmatrix[0][1] = uz[0] * uz[1] * (1 - cos(ome)) - uz[2] * sin(ome);
	rmatrix[0][2] = uz[0] * uz[2] * (1 - cos(ome)) + uz[1] * sin(ome);
	rmatrix[1][0] = uz[0] * uz[1] * (1 - cos(ome)) + uz[2] * sin(ome);
	rmatrix[1][1] = cos(ome) + uz[1] * uz[1] * (1 - cos(ome));
	rmatrix[1][2] = uz[1] * uz[2] * (1 - cos(ome)) - uz[0] * sin(ome);
	rmatrix[2][0] = uz[0] * uz[2] * (1 - cos(ome)) - uz[1] * sin(ome);
	rmatrix[2][1] = uz[1] * uz[2] * (1 - cos(ome)) + uz[0] * sin(ome);
	rmatrix[2][2] = cos(ome) + uz[2] * uz[2] * (1 - cos(ome));
	matrix_vector_multiplication(rmatrix, ux);
	matrix_vector_multiplication(rmatrix, uy);
}
