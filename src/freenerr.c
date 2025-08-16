/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freenerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:11:25 by musajid           #+#    #+#             */
/*   Updated: 2025/08/16 16:22:10 by musajid          ###   ########.fr       */
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
	exit(127);
}

void strerrornExit(void)
{
	strerror(errno);
	exit(EXIT_FAILURE);
}
void	freeall(char **arr, char *str, char *cmd)
{
	freearray(arr);
	free(str);

	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	// // errno = ENOENT;
	// // exit(127);
}

// void comma()
// {
// 	errno = ENOENT;
// 	exit(127);
// }
