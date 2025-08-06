/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: INTRA_LOGIN <INTRA_LOGIN@student.hive.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:40:18 by musajid           #+#    #+#             */
/*   Updated: 2025/05/13 17:57:10 by INTRA_LOGIN      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = (char *)ft_calloc((len + 1), sizeof(char));
	if (!strjoin)
		return (NULL);
	while (s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}

// int	main(void)
// {
// 	char *s1 = "this is";
// 	char *s2 = "wrod";
// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }