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

#include "pipex_bonus.h"

void	wait_tasks(t_all *all, char **argv)
{
	int		i;
	char	flag;

	i = -1;
	flag = 0;
	if (!ft_strncmp(argv[1], "here_doc", INT_MAX))
		flag = 1;
	while (++i < all->ene)
	{
		waitpid(all->subtask[i], &all->status, 0);
		if (i < all->ene - 1 && close(all->pipefd[i][1]))
			clean_exit(all, 0);
		if (i == 0 && flag == 1 && unlink(".here_doc") == -1)
			perror(0);
		if (i > 0 && close(all->pipefd[i - 1][0]) == -1)
			perror(0);
	}
}

void	setup_pipes(t_all *all)
{
	int	i;

	i = 0;
	all->pipefd = malloc(8 * all->ene);
	if (!all->pipefd)
		clean_exit(all, 0);
	while (i < all->ene - 1)
	{
		if (pipe(all->pipefd[i++]) == -1)
			clean_exit(all, 0);
	}
}

void	initialize(t_all *all)
{
	all->cmd = 0;
	all->paths = 0;
	all->pipefd = 0;
	all->subtask = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_all	all;

	check_arguments(&all, argv, argc);
	initialize(&all);
	obtain_paths(&all, envp);
	parse_commands(&all, argv);
	setup_pipes(&all);
	task_forking(&all, infile(&all, argv), argv, envp);
	wait_tasks(&all, argv);
	free_all(&all);
	return (all.status);
}
