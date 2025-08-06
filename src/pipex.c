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

static void	freearray(char **arr)
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

static	void	error(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

static char	*get_path(char **envp)
{
    int		i;

    i = 0;
    if (!envp[i])
        return (NULL);
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}
//step by step
//spliting the PATH
// splitting the COMMAND
// adding '/' to end of every split COMMAND
// checking for the access to execute
static void    splitnfit(char *cmdstr, char **envp)
{
    char *path;
    int i;
    char **paths;
    char **splitcmd;
    char *cmd;
	int	found;

    i = 0;
    paths = ft_split(get_path(envp), ':');
    splitcmd = ft_split(cmdstr, ' ');
    cmd = ft_strjoin("/", splitcmd[0]);
    while (paths[i])
    {
        path = ft_strjoin(paths[i], cmd);
        if (access(path, X_OK) == 0)
		{
			found = 1;
			break;
		}
        free(path);
        i++;
    }
	if (!found)
		error();
    if (execve(path, splitcmd, envp) == -1)
    {
        freearray(paths);
        freearray(splitcmd);
        free(cmd);
        free(path);
        error();
    }
}

//in dup2(fd[1], 1) if 1 is prev. on tty, it redirects to same thing fd[1]/pipe_end points to 
static void    cmd1exe(int infile, int fd[2], char *av, char **envp)
{
    dup2(infile, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    splitnfit(av, envp);

}

static void    cmd2exe(int outfile, int fd[2], char *av, char **envp)
{
    dup2(outfile, STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    splitnfit(av, envp);
}

static void init_struct(main_struct *i)
{
    i->fd[0] = -1;
    i->fd[1] = -1;
    i->infile = -1;
    i->outfile = -1;
}

static void	close_all(main_struct *i)
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

int main(int ac, char **av, char **envp)
{
	main_struct i;

	init_struct(&i);
    pipe(i.fd);
    if (ac != 5)
        return (printf("arguements should be like ./pipex infile cmd1 cmd2 outfile\n"));
    i.infile = open(av[1], O_RDONLY);
	if (i.infile < 0)
		error();
    i.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (i.outfile < 0)
		error();
	i.pid1 = fork();
    if (i.pid1 == 0)
        cmd1exe(i.infile, i.fd, av[2], envp);
    i.pid2 = fork();
    if (i.pid2 == 0)
 	{
		cmd2exe(i.outfile, i.fd, av[3], envp);
	}
	close(i.fd[0]);
	close(i.fd[1]);
 	waitpid(i.pid1, NULL, 0);
	waitpid(i.pid2, NULL, 0);
	close_all(&i);
    return (0);
}

