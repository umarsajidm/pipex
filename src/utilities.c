/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:25:08 by musajid           #+#    #+#             */
/*   Updated: 2025/08/13 18:47:35 by musajid          ###   ########.fr       */
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

static void	freeErrorExit(char **arr)
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

static char	**get_path(char **envp)
{
	int		i;
	char	**paths;


	i = 0;
	if (!envp[i])
		return (NULL);
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			{
				paths = ft_split((envp[i] + 5), ':');
				if (!paths || !*paths)
					freeErrorExit(paths);
				return(paths);
			}
		i++;
	}
	return (NULL);
}

static char *mycmd(char *cmd)
{
	char **splitcmd;

	if (!cmd)
		strerror(errno);
	splitcmd = ft_split(cmd, ' ');
	if (!splitcmd || !*splitcmd)
		freeErrorExit(splitcmd);
	return(ft_strjoin("/", splitcmd[0]));
}

static int check_path(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	free(path);
	return (0);
}
static char *fndnexe(char *cmd, char**envp)
{
	int	found;
	int	i;
	char	**paths;
	char	*path;
	char	*pathcmd;

	i = 0;
	found = 0;
	pathcmd = mycmd(cmd);
	paths = get_path(envp);
	if (!paths || !*paths)
		freeErrorExit(paths);
	while(paths[i])
	{
		path = ft_strjoin(paths[i], pathcmd);
		if (check_path(path))
		{
			found = 1;
			break;
		}
		i++;
	}
	if (!found)
		strerror(errno);
	return (path);
}

static void 	execution(char *cmd, char **envp)
{
	char	*path;
	char	**splitcmd;

	path = fndnexe(cmd, envp);
	splitcmd = ft_split(cmd, ' ');
	if (!splitcmd || !*splitcmd)
		freeErrorExit(splitcmd);
	if (execve(path, splitcmd,  envp) == -1)
	{
		freearray(splitcmd);
		free(path);
		strerrornExit();
	}

}

void	cmd1exe(int fd[2], char **av, char **envp)
{
	int infile;

	infile = open(av[1], O_RDONLY);
	if(infile < 0)
		strerrornExit();
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	execution(av[2], envp);
}

void	cmd2exe(int fd[2], char **av, char **envp)
{
	int outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		strerrornExit();
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execution(av[3], envp);
}
void	close_all(main_struct *i)
{
	if (i->fd[0] != 0)
		close(i->fd[0]);
	if (i->fd[1] != 0)
		close (i->fd[1]);
	if (i->infile != 0)
		close (i->infile);
	if (i->outfile != 0)
		close (i->outfile);
}

