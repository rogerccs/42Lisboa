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

#include "pipex_bonus.h"

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
	int	i;

	i = 0;
	all->subtask = malloc(4 * all->ene);
	if (!all->subtask)
		clean_exit(all, 0);
	all->cmd = malloc(8 * all->ene + 8);
	if (!all->cmd)
		clean_exit(all, 0);
	all->cmd[all->ene] = 0;
	while (i < all->ene)
	{
		all->cmd[i] = quote_split(argv[i + 2 + !ft_strncmp(argv[1],
					"here_doc", INT_MAX)], ' ');
		clean_quotes(all, all->cmd[i++]);
	}
}

void	check_arguments(t_all *all, char **argv, int argc)
{
	if (argc == 1)
	{
		write(2, "Program must receive 4 or more arguments\n", 41);
		exit(1);
	}
	if (!ft_strncmp(argv[1], "here_doc", INT_MAX))
	{
		if (argc < 6)
			write(2, "Program requires 5 or more arguments\n", 37);
		if (argc < 6)
			exit(1);
		all->ene = argc - 4;
	}
	else
	{
		if (argc < 5)
			write(2, "Program requires 4 or more arguments\n", 37);
		if (argc < 5)
			exit(1);
		all->ene = argc - 3;
	}
}
