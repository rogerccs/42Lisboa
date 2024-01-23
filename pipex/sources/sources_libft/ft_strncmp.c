/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <rcastelo@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:05:43 by rcastelo          #+#    #+#             */
/*   Updated: 2023/08/30 12:31:44 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 && s2)
		return (-*s2);
	else if (s1 && !s2)
		return (*s1);
	else if (!s1 && !s2)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		else if (!s1[i])
			return (0);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	printf("strncmp=%i\n", strncmp("test\200", "test\0", 6));
	printf("strncmp=%i\n", ft_strncmp("test\201", "test\0", 6));
	return (0);
}
*/
