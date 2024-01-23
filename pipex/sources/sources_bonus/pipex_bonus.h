/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:18:52 by rcastelo          #+#    #+#             */
/*   Updated: 2023/12/20 14:18:54 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <limits.h>
#include <errno.h>
#include <sys/wait.h>

typedef struct s_all
{
	int		ene;
	int		status;
	int		(*pipefd)[2];
	int		*subtask;	
	char	**paths;
	char	***cmd;
}	t_all;

int		infile(t_all *all, char **argv);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_all(t_all *all);
void	free_table(char **table);
void	clean_exit(t_all *all, char *str);
void	check_arguments(t_all *all, char **argv, int argc);
void	obtain_paths(t_all *all, char **envp);
void	parse_commands(t_all *all, char **argv);
void	nocommand_exit(t_all *all, char *command);
void	nopermission_exit(t_all *all, char *command);
void	first_subtask(t_all *all, int fd, char **envp);
void	run_command(t_all *all, char **cmd, char **envp);
void	task_forking(t_all *all, int fd, char **argv, char **envp);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	**quote_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3);
