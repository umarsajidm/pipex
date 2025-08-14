/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:25:08 by musajid           #+#    #+#             */
/*   Updated: 2025/08/14 17:15:17 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
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

char *pathtoexecute(char **cmd, char**envp)
{
	int	i;
	char	**paths;
	char	*path;
	char	*pathcmd;

	i = 0;
	path = NULL;
	pathcmd = ft_strjoin("/", cmd[0]);
	if (!pathcmd)
		strerrornExit();
	paths = get_path(envp);
	if (!paths || !*paths)
		{
			free(pathcmd);
			freeErrorExit(paths);
		}
	while(paths[i])
	{
		path = ft_strjoin(paths[i], pathcmd);
		if (!path)
		{
			free(pathcmd);
			freearray(paths);
			strerrornExit();
		}
		if (access(path, X_OK) == 0)
		{
			freearray(paths);
			free(pathcmd);
			return (path);
		}
		free(path);
		i++;
	}
	//commmand not found
	free(pathcmd);
	freearray(paths);
	//strerrornExit();
	return (NULL);
	}



void 	execution(char *cmd, char **envp)
{
	char	*path;
	char	**splitcmd;

	if (!cmd)
		strerrornExit();
	splitcmd = ft_split(cmd, ' ');
	if (!splitcmd || !*splitcmd)
		freeErrorExit(splitcmd);
	path = pathtoexecute(splitcmd, envp);
	if (!path)
	{
		freearray(splitcmd);
		strerrornExit();
	}
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
	if (i->fd[0] >= 0)
		close(i->fd[0]);
	if (i->fd[1] >= 0)
		close(i->fd[1]);
	if (i->infile >= 0)
		close(i->infile);
	if (i->outfile >= 0)
		close(i->outfile);
}
