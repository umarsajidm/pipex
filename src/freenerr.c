/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freenerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:11:25 by musajid           #+#    #+#             */
/*   Updated: 2025/08/14 14:12:21 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freearray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	freeErrorExit(char **arr)
{
	if (arr)
		freearray(arr);
	perror("error");
	exit(EXIT_FAILURE);
}

void strerrornExit(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}

