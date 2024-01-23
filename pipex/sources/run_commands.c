/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:26:46 by rcastelo          #+#    #+#             */
/*   Updated: 2023/12/19 14:26:47 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_command(t_all *all, char **cmd, char **envp)
{
	int		i;
	char	*original;
	char	*absolute;

	i = 0;
	original = cmd[0];
	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == -1)
		nopermission_exit(all, cmd[0]);
	if (access(cmd[0], F_OK) == 0 && execve(cmd[0], cmd, envp) == -1)
		clean_exit(all, cmd[0]);
	while (all->paths && all->paths[i])
	{
		absolute = ft_strjoinjoin(all->paths[i++], "/", original);
		if (!absolute)
			clean_exit(all, 0);
		cmd[0] = absolute;
		if (!access(absolute, F_OK) && access(absolute, X_OK) == -1)
			nopermission_exit(all, absolute);
		if (!access(absolute, F_OK) && execve(absolute, cmd, envp) < 0)
			clean_exit(all, absolute);
		free(absolute);
		cmd[0] = original;
	}
}
