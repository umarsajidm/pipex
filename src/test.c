#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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

#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
    char *path = get_path(envp);
    if (path)
        printf("%s\n", path);
    else
        printf("PATH not found.\n");
    return 0;
}
