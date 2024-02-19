/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:08 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/19 15:01:54 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
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
	char	**av;
	char	**env;
	int		ac;
	int		i;
	int		heredoc;
	int		k;
	int		*pid;
	int		filein;
	int		fileout;
}			t_pipex;

typedef struct s_struct
{
	int		i;
	int		k;
	char	*ptr;
	char	*ptr1;
	char	*ptr2;
}			t_struct;

void		error(int cmd, char *ptr, char *p);
void		here_doc(t_pipex pipex, char *av, int ac, char **env);
char		*grep_var(char *line);
char		*is_it_in(char **env, char *ptr);
void		free_array(char **str);
char		*find_path(char **env, char *cmd, t_pipex pipex);
void		fork_pro(char *av, t_pipex pipex, int k, int fd[2]);
int			wait_pid(int *pid, int status, int cmd_num);
int			last_cmd(char *av, t_pipex pipex, char **env, int fd[2]);
int			d_is_in(char *str);
void		put_with_var(char *str, int vars, int fd, char **env);
void		heredoc(t_pipex pipex, char *p, int fd[], char **env);

#endif