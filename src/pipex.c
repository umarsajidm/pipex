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
}

void	strerrornexit(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

static	void	cmd1exe(int fd[2], char **av, char **envp)
{
	int	infile;

	if (access(av[1], R_OK) == -1)
		perror(av[1]);
	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		strerrornexit();
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execution(av[2], envp);
}

static	void	cmd2exe(int fd[2], char **av, char **envp)
{
	int	outfile;

	if (access(av[4], W_OK) == -1)
		perror(av[4]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		strerrornexit();
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execution(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	main_struct	i;

	init_struct(&i);
	pipe(i.fd);
	if (ac != 5)
		return (printf("should be ./pipex infile cmd1 cmd2 outfile\n"));
	i.pid1 = fork();
	if (i.pid1 == -1)
		perror("fork");
	if (i.pid1 == 0)
		cmd1exe(i.fd, av, envp);
	i.pid2 = fork();
	if (i.pid2 == -1)
		perror("fork");
	if (i.pid2 == 0)
		cmd2exe(i.fd, av, envp);
	close(i.fd[0]);
	close(i.fd[1]);
	waitpid(i.pid1, NULL, 0);
	waitpid(i.pid2, &i.status, 0);
	if (WIFEXITED(i.status))
		return (WEXITSTATUS(i.status));
	return (1);
}
