/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:21:08 by rcastelo          #+#    #+#             */
/*   Updated: 2024/01/15 15:21:09 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_to_fd(t_all *all, char **argv)
{
	int		i;
	int		fd;
	char	*line;

	fd = open(".here_doc", O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		clean_exit(all, ".here_doc");
	line = 0;
	argv[2] = ft_strjoin(argv[2], "\n");
	if (!argv[2])
		clean_exit(all, 0);
	while (ft_strncmp(line, argv[2], INT_MAX))
	{
		i = 0;
		while (line && line[i])
			i++;
		write(fd, line, i);
		write(1, "heredoc> ", 9);
		if (line)
			free(line);
		line = get_next_line(0);
	}
	free(line);
	free(argv[2]);
	close(fd);
}

int	nofile_pipe(t_all *all, char *filename)
{
	int	protection_pipe[2];

	perror(filename);
	if (pipe(protection_pipe) == -1)
		clean_exit(all, 0);
	if (close(protection_pipe[1]) < 0)
		perror(0);
	return (protection_pipe[0]);
}

int	allocate_file(t_all *all, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		return (nofile_pipe(all, filename));
	if (fd != -1 && dup2(fd, 0) == -1)
		clean_exit(all, 0);
	return (fd);
}

int	infile(t_all *all, char **argv)
{
	int	fd;

	if (!ft_strncmp(argv[1], "here_doc", INT_MAX))
	{
		heredoc_to_fd(all, argv);
		fd = open(".here_doc", O_RDONLY, 0644);
		if (fd == -1)
			clean_exit(all, 0);
		return (fd);
	}
	else 
		return (allocate_file(all, argv[1]));
}
