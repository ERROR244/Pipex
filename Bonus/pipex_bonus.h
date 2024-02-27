/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:04:19 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/27 14:39:03 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
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
	int		here_doc;
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

void		ft_dup2(int fd, int std);
int			ft_fork(void);
void		ft_close(int fd);
t_pipex		fop(int flag, t_pipex p, int fd[2]);
void		error(int cmd, char *ptr, char *p);
void		here_doc(t_pipex pipex);
char		*grep_var(char *line);
char		*is_it_in(char **env, char *ptr);
void		free_array(char **str);
char		*find_path(char **env, char *cmd, t_pipex pipex);
void		fork_pro(char *av, t_pipex pipex, int k, int fd[2]);
int			wait_pid(int *pid, int status, int cmd_num);
int			last_cmd(char *av, t_pipex pipex, char **env, int fd[2]);
int			d_is_in(char *str);
void		put_with_var(char *str, int fd, char **env);
void		heredoc(t_pipex pipex, char *p, char **env);

#endif