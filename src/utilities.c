/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@hive.student.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:25:08 by musajid           #+#    #+#             */
/*   Updated: 2025/08/17 19:04:30 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


//getting the path form environment
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
					freeError(paths);// need to check that for exit
				return(paths);
			}
		i++;
	}
	return (NULL);
}

//searching for the executable path of our command in the environment path
char *pathtoexecute(char **cmd, char**envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*pathcmd;

	i = 0;
	path = NULL;
	pathcmd = ft_strjoin("/", cmd[0]);
	if (!pathcmd) 
		freeError(&pathcmd);
	paths = get_path(envp);
	if (!paths || !*paths)
		freestrnarrExit(paths, pathcmd, 127);
	while(paths[i])
	{
		path = ft_strjoin(paths[i], pathcmd);
		if (!path)
			freestrnarrExit(paths, pathcmd, 1);
		if (access(path, X_OK) == 0)// form there
		{
			freestrnarrExit(paths, pathcmd, 0);
			return (path);
		}
		free(path);
		i++;
	}
	freeall(paths, pathcmd, cmd[0]);
	return (NULL);
}
void	checking(char *path)
{
	if ((access(path, F_OK) == 0) && (access(path, X_OK) == -1))
		errno = EACCES;
	if (access(path, X_OK) == 0)
		return ;
	if (access(path, X_OK))
		errno = ENOENT;
}
void 	execution(char *cmd, char **envp)
{
	char	*path;
	char	**splitcmd;

	if (!cmd)
		strerrornExit();
	splitcmd = ft_split(cmd, ' ');
	if (!splitcmd || !*splitcmd)
		freeError(splitcmd); //need to check that for exit
	path = pathtoexecute(splitcmd, envp);
	if (path == NULL)
		commandNotFound(splitcmd);
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

	if (access(av[1], R_OK) == -1)
		perror(av[1]);
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

	if (access(av[4], W_OK) == -1)
		perror(av[4]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile < 0)
		strerrornExit();
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	execution(av[3], envp);
}
