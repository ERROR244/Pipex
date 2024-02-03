/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 01:16:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/03 01:51:35 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	ft_putstr_fd("Error:\n", 2);
	exit(1);
}

char	*find_path(char **env, char *cmd, t_pipex pipex)
{
	pipex.i = 0;
	while (env[pipex.i])
	{
		pipex.ptr = ft_strnstr(env[pipex.i], "PATH", ft_strlen("PATH"));
		if (pipex.ptr != NULL)
			break ;
		pipex.i++;
	}
	pipex.str = ft_strdup(pipex.ptr + 5);
	pipex.paths = ft_split(pipex.str, ':');
	pipex.i = 0;
	while (pipex.paths[pipex.i])
	{
		pipex.str = ft_strjoin(pipex.paths[pipex.i], '/', cmd);
		if (access(pipex.str, F_OK) == 0)
			return (pipex.str);
		free(pipex.str);
		pipex.i++;
	}
	return (NULL);
}

void	child(char **av, int fd[], t_pipex pipex, char **env)
{
	pipex.cmd1 = ft_split(av[2], ' ');
	pipex.path1 = find_path(env, pipex.cmd1[0], pipex);
	pipex.filein = open(av[1], O_RDONLY, 0777);
	if (pipex.filein == -1)
		error();
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(pipex.filein, STDIN_FILENO);
	close(fd[1]);
	execve(pipex.path1, pipex.cmd1, env);
	ft_putstr_fd("Error: command not found\n", 2);
	exit(EXIT_FAILURE);
}

void	parent(char **av, int fd[], t_pipex pipex, char **env)
{
	pipex.cmd2 = ft_split(av[3], ' ');
	pipex.path2 = find_path(env, pipex.cmd2[0], pipex);
	waitpid(pipex.pid, NULL, 0);
	pipex.fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex.fileout == -1)
		error();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(pipex.fileout, STDOUT_FILENO);
	close(fd[0]);
	execve(pipex.path2, pipex.cmd2, env);
	ft_putstr_fd("Error: command not found\n", 2);
	exit(EXIT_FAILURE);
}
