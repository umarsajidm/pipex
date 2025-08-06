#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void freearray(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char * get_path(char **envp)
{
    int i = 0;
    char **path;
    path = envp;
    if (!path[i])
        return NULL;
    while (path[i])
    {
        if (strncmp(path[i], "PATH=", 5) == 0)
            return (path[i] + 5);
        i++;
    }
    return NULL; 
}
void    splitnfit(char *cmdstr, char **envp)
{
    char *path;
    int i = 0;
    char **paths = ft_split(get_path(envp), ':'); //spliting the PATH
    char **splitcmd = ft_split(cmdstr, ' '); // splitting the COMMAND
    char *cmd = ft_strjoin("/", splitcmd[0]); // adding '/' to end of every split COMMAND
    while (paths[i])
    {
        path = ft_strjoin(paths[i], cmd);
        if (access(path, X_OK) == 0) // checking for the access to execute
            break;
        free(path);
        i++;
    }
    if (execve(path, splitcmd, envp) == -1) // invoking the execve to execute the command
    {
        perror(execve);
        freearray(paths);
        freearray(splitcmd);
        free(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
}



int main(int ac, char **av, char **envp)
{
    if (ac != 5)
        return (printf("arguements should be 5 incl. prog. name\n"));
    int infile_fd = open(av[1], O_RDONLY);
    dup2(infile_fd, STDIN_FILENO);
    splitnfit(av[2], envp);
    return 0;
}