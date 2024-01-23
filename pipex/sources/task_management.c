/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:29:35 by rcastelo          #+#    #+#             */
/*   Updated: 2024/01/11 12:29:37 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_subtask(t_all *all, char *filename, char **envp)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		clean_exit(all, filename);
	if (dup2(fd, 1) == -1)
		clean_exit(all, 0);
	if (close(fd) == -1)
		perror(0);
	if (dup2(all->pipefd[0], 0) == -1)
		clean_exit(all, 0);
	if (close(all->pipefd[0]) == -1)
		perror(0);
	if (close(all->pipefd[1]) == -1)
		clean_exit(all, 0);
	if (all->cmd[1][0])
		run_command(all, all->cmd[1], envp);
	nocommand_exit(all, all->cmd[1][0]);
}

void	nofile_pipe(t_all *all, char *filename)
{
	int	protection_pipe[2];

	perror(filename);
	if (pipe(protection_pipe) == -1)
		clean_exit(all, 0);
	if (dup2(protection_pipe[0], 0) < 0)
		clean_exit(all, 0);
	if (close(protection_pipe[0]) < 0)
		perror(0);
	if (close(protection_pipe[1]) < 0)
		clean_exit(all, 0);
}

void	first_subtask(t_all *all, char *filename, char **envp)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		nofile_pipe(all, filename);
	if (fd != -1 && dup2(fd, 0) == -1)
		clean_exit(all, 0);
	if (fd != -1 && close(fd) == -1)
		perror(0);
	if (dup2(all->pipefd[1], 1) == -1)
		clean_exit(all, 0);
	if (close(all->pipefd[0]) == -1)
		perror(0);
	if (close(all->pipefd[1]) == -1)
		perror(0);
	if (all->cmd[0][0])
		run_command(all, all->cmd[0], envp);
	nocommand_exit(all, all->cmd[0][0]);
}

void	task_forking(t_all *all, char **argv, char **envp)
{
	all->subtask[0] = fork();
	if (all->subtask[0] == -1)
		clean_exit(all, 0);
	if (all->subtask[0] == 0)
		first_subtask(all, argv[1], envp);
	all->subtask[1] = fork();
	if (all->subtask[1] == -1)
		clean_exit(all, 0);
	if (all->subtask[1] == 0)
		last_subtask(all, argv[4], envp);
}
