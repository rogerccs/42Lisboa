/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:19:51 by rcastelo          #+#    #+#             */
/*   Updated: 2023/09/04 13:06:45 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static char	*ft_strndup(const char *str, int n, char **output, int k)
{
	int		i;
	char	*new;

	new = malloc(n + 1);
	if (!new)
	{
		i = 0;
		while (i < k)
			free(output[i++]);
		free(output);
		return (new);
	}
	new[n] = 0;
	while (--n >= 0)
		new[n] = str[n];
	return (new);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		ij[2];
	int		k;
	char	**arrstr;

	arrstr = malloc(count_words(s, c) * 8 + 8);
	if (!arrstr)
		return (arrstr);
	arrstr[count_words(s, c)] = 0;
	ij[0] = 0;
	ij[1] = -1;
	k = 0;
	while (s[ij[0]])
	{
		if ((ij[0] == 0 || s[ij[0] - 1] == c) && s[ij[0]] != c)
			ij[1] = ij[0];
		if ((s[ij[0] + 1] == c || s[ij[0] + 1] == 0) && ij[1] != -1)
		{
			arrstr[k] = ft_strndup(&s[ij[1]], ij[0] - ij[1] + 1, arrstr, k);
			if (!arrstr[k++])
				return (0);
			ij[1] = -1;
		}
		ij[0]++;
	}
	return (arrstr);
}
/*
int	main(int argc, char **argv)
{
	int	i;
	char	**words;
	
	if (argc == 3)
	{
		i = 0;
		words = ft_split(argv[1], argv[2][0]);
		while (words[i])
			printf("%s\n", words[i++]);
	}
	return (0);
}
*/
