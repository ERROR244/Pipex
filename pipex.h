/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/11 17:25:45 by ksohail-         ###   ########.fr       */
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
	char	*ptr;
	char	*str;
	char	**cmd;
	char	**paths;
	char	*path;
	int		i;
	int		pid;
	int		filein;
	int		fileout;
}			t_pipex;

void		error(int cmd);
char		*grep_var(char *line);
char		*is_it_in(char **env, char *ptr);
void		free_array(char **str);
char		*find_path(char **env, char *cmd, t_pipex pipex);
void		fork_pro(char *av, t_pipex pipex, char **env);
void		last_cmd(char *av, t_pipex pipex, char **env);
int			d_is_in(char *str);
void		put_with_var(char *str, int vars, int fd, char **env);

#endif