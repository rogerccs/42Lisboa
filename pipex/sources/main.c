/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:42:46 by rcastelo          #+#    #+#             */
/*   Updated: 2023/12/19 11:42:49 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_tasks(t_all *all)
{
	waitpid(all->subtask[0], &all->status, 0);
	if (close(all->pipefd[1]) == -1)
		clean_exit(all, 0);
	waitpid(all->subtask[1], &all->status, 0);
	if (close(all->pipefd[0]) == -1)
		perror(0);
}

void	setup_pipe(t_all *all)
{
	if (pipe(all->pipefd) == -1)
		clean_exit(all, 0);
}

void	initialize(t_all *all)
{
	all->cmd[0] = 0;
	all->paths = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	if (argc != 5)
		write(2, "Program must receive 4 arguments\n", 33);
	if (argc != 5)
		exit(1);
	initialize(&all);
	obtain_paths(&all, envp);
	parse_commands(&all, argv);
	setup_pipe(&all);
	task_forking(&all, argv, envp);
	wait_tasks(&all);
	free_all(&all);
	return ((all.status & 0xff00) >> 8);
}
