/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:44:13 by rcastelo          #+#    #+#             */
/*   Updated: 2024/01/08 18:44:14 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strjoinjoin(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	int		k;
	char	*out;

	i = 0;
	j = 0;
	k = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	while (s3 && s3[k])
		k++;
	out = malloc(i + j + k + 1);
	if (!out)
		return (0);
	out[i + j + k] = 0;
	while (--k >= 0)
		out[i + j + k] = s3[k];
	while (--j >= 0)
		out[i + j] = s2[j];
	while (--i >= 0)
		out[i] = s1[i];
	return (out);
}
