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

#include "pipex_bonus.h"

void	last_subtask(t_all *all, char **argv, char **envp)
{
	int	i;
	int	fd;

	i = -1;
	if (!ft_strncmp(argv[1], "here_doc", INT_MAX))
		fd = open(argv[all->ene + 3], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(argv[all->ene + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, 1) == -1)
		clean_exit(all, 0);
	if (close(fd) == -1)
		perror(0);
	if (dup2(all->pipefd[all->ene - 2][0], 0) == -1)
		clean_exit(all, 0);
	while (++i < all->ene - 1)
	{
		if (close(all->pipefd[i][0]) == -1)
			perror(0);
		if (close(all->pipefd[i][1]) == -1)
			clean_exit(all, 0);
	}
	if (all->cmd[all->ene - 1][0])
		run_command(all, all->cmd[all->ene - 1], envp);
	nocommand_exit(all, all->cmd[all->ene - 1][0]);
}

void	middle_subtask(t_all *all, int i, char **envp)
{
	int	j;

	j = -1;
	if (dup2(all->pipefd[i - 1][0], 0) == -1)
		clean_exit(all, 0);
	if (dup2(all->pipefd[i][1], 1) == -1)
		clean_exit(all, 0);
	while (++j < all->ene - 1)
	{
		if (close(all->pipefd[j][0]) == -1)
			perror(0);
		if (close(all->pipefd[j][1]) == -1)
			perror(0);
	}
	if (all->cmd[i][0])
		run_command(all, all->cmd[i], envp);
	nocommand_exit(all, all->cmd[i][0]);
}

void	first_subtask(t_all *all, int fd, char **envp)
{
	int	i;

	i = -1;
	if (dup2(fd, 0) == -1)
		clean_exit(all, 0);
	if (close(fd) == -1)
		perror(0);
	if (dup2(all->pipefd[0][1], 1) == -1)
		clean_exit(all, 0);
	while (++i < all->ene - 1)
	{
		if (close(all->pipefd[i][0]) == -1)
			perror(0);
		if (close(all->pipefd[i][1]) == -1)
			perror(0);
	}
	if (all->cmd[0][0])
		run_command(all, all->cmd[0], envp);
	nocommand_exit(all, all->cmd[0][0]);
}

void	task_forking(t_all *all, int fd, char **argv, char **envp)
{
	int	i;

	i = 0;
	all->subtask[0] = fork();
	if (all->subtask[0] == -1)
		clean_exit(all, 0);
	if (all->subtask[0] == 0)
		first_subtask(all, fd, envp);
	if (close(fd) == -1)
		perror(0);
	while (++i < all->ene - 1)
	{
		all->subtask[i] = fork();
		if (all->subtask[i] == -1)
			clean_exit(all, 0);
		if (all->subtask[i] == 0)
			middle_subtask(all, i, envp);
	}
	all->subtask[all->ene - 1] = fork();
	if (all->subtask[all->ene - 1] == -1)
		clean_exit(all, 0);
	if (all->subtask[all->ene - 1] == 0)
		last_subtask(all, argv, envp);
}
