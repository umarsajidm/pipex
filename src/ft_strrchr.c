/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: INTRA_LOGIN <INTRA_LOGIN@student.hive.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:10:54 by musajid           #+#    #+#             */
/*   Updated: 2025/05/13 17:59:58 by INTRA_LOGIN      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (1)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		if (i == 0)
			break ;
		i--;
	}
	return (NULL);
}
