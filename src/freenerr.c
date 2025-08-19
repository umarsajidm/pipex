/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freenerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@hive.student.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:11:25 by musajid           #+#    #+#             */
/*   Updated: 2025/08/17 15:48:50 by musajid          ###   ########.fr       */
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
void	freestr(char *str)
{
	if (str)
		free(str);
}
void freestrnarrExit(char **arr, char *str, int i)
{
	freearray(arr);
	free(str);
	if (1)
		exit(EXIT_FAILURE);
	if (126)
	{
		errno = EACCES;
		exit(126);
	}
	if (127)
	{
		errno = ENOENT;
		exit(127);
	}
}
void	freeError(char **arr)
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
}

void commandNotFound(char **arr)
{
	freearray(arr);
	errno = ENOENT;
	exit(127);
}
