/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:23:51 by musajid           #+#    #+#             */
/*   Updated: 2025/08/06 13:23:51 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

static	void	init_struct(main_struct	*i)
{
	i->fd[0] = -1;
	i->fd[1] = -1;
	i->infile = -1;
	i->outfile = -1;
}


int	main(int ac, char **av, char **envp)
{
	main_struct	i;
	int status;

	init_struct(&i);
	pipe(i.fd);
	if (ac != 5)
		return (printf("should be ./pipex infile cmd1 cmd2 outfile\n"));
	i.pid1 = fork();
	if (i.pid1 == 0)
		cmd1exe(i.fd, av, envp);
	i.pid2 = fork();
	if (i.pid2 == 0)
		cmd2exe(i.fd, av, envp);
	close(i.fd[0]);
	close(i.fd[1]);
	waitpid(i.pid1, NULL, 0);
	waitpid(i.pid2, &status, 0);
	close_all(&i);
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return (1);
}

