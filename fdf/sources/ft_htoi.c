/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcastelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:07:21 by rcastelo          #+#    #+#             */
/*   Updated: 2023/11/20 14:07:24 by rcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_htoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	i += 2;
	while ((nptr[i] >= '0' && nptr[i] <= '9') 
		|| (nptr[i] >= 'A' && nptr[i] <= 'F')
		|| (nptr[i] >= 'a' && nptr[i] <= 'f'))
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			res = res * 16 + (nptr[i++] - '0');
		else if (nptr[i] >= 'A' && nptr[i] <= 'F')
			res = res * 16 + (nptr[i++] - 'A') + 10;
		else
			res = res * 16 + (nptr[i++] - 'a') + 10;
	}
	return (res);
}
