/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@hive.student.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:44:59 by musajid           #+#    #+#             */
/*   Updated: 2025/08/17 15:17:43 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <error.h>
# include <errno.h>
# include <unistd.h>

typedef struct f_struct
{
    char    *path;
    int     i;
    char    **paths;
    char    **splitcmd;
    char    *cmd;
	int	    found;
}   t_struct;

typedef struct s_struct
{
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     status;
}   main_struct;

int	main(int ac, char **av, char **envp);

void	close_all(main_struct *i);
void	splitnfit(char *cmdstr, char **envp);

void	freeError(char **arr);
void strerrornExit(void);
void	freearray(char **arr);
void	freeall(char **arr, char *str, char *cmd);
void	commandNotFound(char **arr);
void freestrnarrExit(char **arr, char *str, int i)

char	**get_path(char **envp);
int 	check_path(char *path);
char 	*pathtoexecute(char **cmd, char**envp);
void 	execution(char *cmd, char **envp);

void	cmd1exe(int fd[2], char **av, char **envp);
void	cmd2exe(int fd[2], char **av, char **envp);


#endif
