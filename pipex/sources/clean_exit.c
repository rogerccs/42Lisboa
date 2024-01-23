/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:03:47 by rcastelo          #+#    #+#             */
/*   Updated: 2023/12/22 18:03:49 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_table(char **table)
{
	int	i;

	if (!table)
		return ;
	i = 0;
	while (table[i])
		free(table[i++]);
	free(table);
}

void	free_all(t_all *all)
{
	free_table(all->paths);
	free_table(all->cmd[0]);
	free_table(all->cmd[1]);
}

void	nopermission_exit(t_all *all, char *command)
{
	perror(command);
	free_all(all);
	exit(126);
}

void	nocommand_exit(t_all *all, char *command)
{
	int		i;
	char	*message;

	i = 0;
	message = ft_strjoinjoin("Command not found: ", command, "\n");
	while (message[i])
		i++;
	write(2, message, i);
	free(message);
	free_all(all);
	exit(127);
}

void	clean_exit(t_all *all, char *str)
{
	perror(str);
	free_all(all);
	exit(1);
}
