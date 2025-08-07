/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musajid <musajid@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:44:59 by musajid           #+#    #+#             */
/*   Updated: 2025/08/07 15:26:17 by musajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

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
void	freearray(char **arr);
void	error(void);

#endif
