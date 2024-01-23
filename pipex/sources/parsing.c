/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:06:15 by rcastelo          #+#    #+#             */
/*   Updated: 2024/01/08 18:06:16 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	obtain_paths(t_all *all, char **envp)
{
	char	**std;
	char	*paths;

	std = ft_split("/usr/bin", ':');
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			free_table(std);
			paths = ft_strjoin(*envp, ":/usr/bin");
			if (!paths)
				clean_exit(all, 0);
			all->paths = ft_split(paths, ':');
			free(paths);
			if (!all->paths)
				clean_exit(all, 0);
			return ;
		}
		envp++;
	}
	all->paths = std;
	return ;
}

void	clean_quotes(t_all *all, char **table)
{
	int		i;
	int		quotes;
	char	*word;

	while (*table)
	{
		i = -1;
		quotes = 0;
		while ((*table)[++i])
		{
			if ((*table)[i] == '\'')
				quotes++;
		}
		word = malloc(i - quotes + 1);
		if (!word)
			clean_exit(all, 0);
		word[i - quotes] = 0;
		while (--i >= 0)
		{
			if ((*table)[i] != '\'' || !quotes--)
				word[i - quotes] = (*table)[i]; 
		}
		free(*table);
		*table++ = word;
	}
}

void	parse_commands(t_all *all, char **argv)
{
	all->cmd[0] = quote_split(argv[2], ' ');
	clean_quotes(all, all->cmd[0]);
	all->cmd[1] = quote_split(argv[3], ' ');
	clean_quotes(all, all->cmd[1]);
}
