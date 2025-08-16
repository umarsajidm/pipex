/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:44:59 by musajid           #+#    #+#             */
/*   Updated: 2025/08/16 16:22:50 by musajid          ###   ########.fr       */
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
    int     infile;
    int     outfile;
    pid_t   pid1;
    pid_t   pid2;
}   main_struct;

int	main(int ac, char **av, char **envp);

void	close_all(main_struct *i);
void	splitnfit(char *cmdstr, char **envp);

void	freeErrorExit(char **arr);
void strerrornExit(void);
void	freearray(char **arr);
void	freeall(char **arr, char *str, char *cmd);
// void	commandNotFound();

char	**get_path(char **envp);
int 	check_path(char *path);
char 	*pathtoexecute(char **cmd, char**envp);
void 	execution(char *cmd, char **envp);

void	cmd1exe(int fd[2], char **av, char **envp);
void	cmd2exe(int fd[2], char **av, char **envp);


#endif
