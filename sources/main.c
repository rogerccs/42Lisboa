/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:08:11 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/10 16:08:13 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	obtain_length(char **array, char flag)
{
	int		i;
	int		j;
	char	*str;

	str = array[0];
	if (flag == 'x')
	{
		i = 0;
		j = 0;
		while (str[i])
		{
			if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
				j++;
			i++;
		}
		return (j);
	}
	else
	{
		i = 0;
		while (array[i])
			i++;
		return (i);
	}
}

void	obtain_matrix(t_all *all, char **ls)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	all->matrix = malloc(all->ly * 8 + 8);
	all->matrix[all->ly] = 0;
	while (++i < all->ly)
	{
		all->matrix[i] = malloc(all->lx * 16);
		j = 0;
		k = 0;
		while (ls[i][k])
		{
			if ((k == 0 || ls[i][k - 1] == ' ') && ls[i][k] != ' ')
			{
				all->matrix[i][j++].z = ft_atoi(&ls[i][k]);
				all->matrix[i][j - 1].cor = 0;
			}
			if (k != 0 && ls[i][k - 1] == ',')
				all->matrix[i][j - 1].cor = ft_htoi(&ls[i][k]);
			k++;
		}
	}
}

char	**get_lines(int fd)
{
	int		i;
	char	**lines;
	char	**lines_temp;

	i = 0;
	lines = 0;
	while (++i)
	{
		lines_temp = malloc(8 * (i + 1));
		if (!lines_temp)
			malloc_exit();
		lines_temp[i - 1] = get_next_line(fd);
		lines_temp[i] = 0;
		if (lines_temp[i - 1] == 0)
		{
			free(lines_temp);
			return (lines);
		}
		while (lines && *lines)
			*lines_temp++ = *lines++;
		if (lines)
			free(lines - i + 1);
		lines = lines_temp - i + 1;
	}
	return (0);
}

void	process_arguments(t_all *all, char **argv)
{
	int		i;
	int		fd;
	char	**file_lines;

	if (!argv[1])
	{
		write(1, "Requires one argument, a filename\n", 34);
		exit(0);
	}
	else if (argv[2])
	{
		write(1, "Requires only one argument, a filename\n", 39);
		exit(0); 
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		invalid_fd_exit();
	file_lines = get_lines(fd);
	all->lx = obtain_length(file_lines, 'x');
	all->ly = obtain_length(file_lines, 'y');
	obtain_matrix(all, file_lines);
	i = 0;
	while (file_lines[i])
		free(file_lines[i++]);
	free(file_lines);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_img	img;
	t_all	all;

	(void) argc;
	all.mlx = &mlx;
	all.img = &img;
	process_arguments(&all, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "Fil de Fer");
	fildefer(&all);
	mlx_hook(mlx.win, 2, 1L, key_pressed, &all);
	mlx_hook(mlx.win, 3, 1L << 1, key_released, &all);
	mlx_hook(mlx.win, 4, 1L << 2, mouse_pressed, &all);
	mlx_hook(mlx.win, 17, 1L << 17, clean_exit, &all);
	mlx_loop_hook(mlx.mlx, render, &all);
	mlx_loop(mlx.mlx);
	return (0);
}
