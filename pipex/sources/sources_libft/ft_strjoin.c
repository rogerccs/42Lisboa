/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:35:54 by rcastelo          #+#    #+#             */
/*   Updated: 2023/08/30 18:46:39 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	out = malloc(i + j + 1);
	if (!out)
		return (out);
	out[i + j] = 0;
	while (--j >= 0)
		out[i + j] = s2[j];
	while (--i >= 0)
		out[i] = s1[i];
	return (out);
}
