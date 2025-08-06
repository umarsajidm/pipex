/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: INTRA_LOGIN <INTRA_LOGIN@student.hive.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:32:19 by INTRA_LOGIN       #+#    #+#             */
/*   Updated: 2025/04/28 14:17:49 by INTRA_LOGIN      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*s_dup;

	s_dup = (char *)malloc(ft_strlen(s) + 1);
	i = 0;
	if (!s_dup)
		return (NULL);
	while (s[i] != '\0')
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}

// int	main(void)
// {
// 	const char *s = "this is me ";
// 	printf("%s", ft_strdup(s));
// 	return (0);
// }