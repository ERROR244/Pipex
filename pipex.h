/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/03 01:56:27 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib/mylib.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		i;
	int		pid;
	char	*ptr;
	char	*str;
	int		filein;
	int		fileout;
	char	**cmd2;
	char	**cmd1;
	char	**paths;
	char	*path1;
	char	*path2;
}			t_pipex;

void		error(void);
char		*find_path(char **env, char *cmd, t_pipex pipex);
void		child(char **av, int fd[], t_pipex pipex, char **env);
void		parent(char **av, int fd[], t_pipex pipex, char **env);
void		pipex(int fd[], char **av, char **env);

#endif