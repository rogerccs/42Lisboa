/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:55:43 by rcastelo          #+#    #+#             */
/*   Updated: 2024/01/08 18:55:47 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static char	*ft_strndup(const char *str, int n, char ***table, int k)
{
	int		i;
	char	*new;

	new = malloc(n + 1);
	if (!new)
	{
		i = 0;
		while (i < k)
			free((*table)[i++]);
		free(*table);
		*table = 0;
		return (0);
	}
	new[n] = 0;
	while (--n >= 0)
		new[n] = str[n];
	return (new);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	aps;
	int	count;

	i = 0;
	aps = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c && !(aps % 2))
			count++;
		if (s[i] == '\'')
			aps++;
		i++;
	}
	return (count);
}

static char	**initialize_table(char const *s, char c)
{
	int		words;
	char	**table;

	words = count_words(s, c);
	table = malloc(words * 8 + 8);
	if (!table)
		return (0);
	table[words] = 0;
	return (table);
}

char	**quote_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		qt;
	char	**table;

	i = -1;
	j = -1;
	k = 0;
	qt = 0;
	table = initialize_table(s, c);
	while (table && s[++i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c && !(qt % 2))
			j = i;
		if (s[i] == '\'')
			qt++;
		if (((s[i + 1] == c && !(qt % 2)) || s[i + 1] == 0) && j != -1)
		{
			table[k] = ft_strndup(&s[j], i - j + 1, &table, k);
			k++;
			j = -1;
		}
	}
	return (table);
}
