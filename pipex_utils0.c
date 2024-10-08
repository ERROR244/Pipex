/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 01:16:23 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/27 17:30:33 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*is_it_in(char **env, char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (str == NULL)
		return (NULL);
	while (env[i])
	{
		ptr = ft_strnstr(env[i], str, ft_strlen(str));
		if (ptr != NULL)
			return (ptr);
		i++;
	}
	return (NULL);
}

char	*find_path(char **env, char *cmd, t_pipex pipex)
{
	int	i;

	i = 0;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	pipex.ptr = is_it_in(env, "PATH");
	pipex.str = ft_strdup(pipex.ptr + 5);
	pipex.paths = ft_split(pipex.str, ':');
	i = 0;
	free(pipex.str);
	while (pipex.paths[i])
	{
		pipex.str = ft_strjoin(pipex.paths[i], '/', cmd);
		if (access(pipex.str, F_OK) == 0)
		{
			free_array(pipex.paths);
			return (pipex.str);
		}
		free(pipex.str);
		i++;
	}
	free_array(pipex.paths);
	return (NULL);
}

void	fork_pro(char *av, t_pipex pipex, int k, int fd[2])
{
	pipex.pid[k] = ft_fork();
	if (pipex.pid[k] == 0)
	{
		ft_close(fd[0]);
		ft_close(pipex.fileout);
		if (av[0] == '\0')
			error(5, NULL, NULL);
		pipex.cmd = ft_split(av, ' ');
		pipex.path = find_path(pipex.env, pipex.cmd[0], pipex);
		ft_dup2(pipex.filein, STDIN_FILENO);
		ft_dup2(fd[1], STDOUT_FILENO);
		ft_close(fd[1]);
		ft_close(pipex.filein);
		execve(pipex.path, pipex.cmd, pipex.env);
		if (pipex.path)
			free(pipex.path);
		free_array(pipex.cmd);
		error(1, av, NULL);
	}
	close(fd[1]);
	close(pipex.filein);
}

int	last_cmd(char *av, t_pipex pipex, char **env, int fd[2])
{
	pipex.pid[pipex.k] = ft_fork();
	if (pipex.pid[pipex.k] == 0)
	{
		if (av[0] == '\0')
			error(6, NULL, NULL);
		pipex.cmd = ft_split(av, ' ');
		pipex.path = find_path(env, pipex.cmd[0], pipex);
		ft_dup2(pipex.filein, STDIN_FILENO);
		ft_dup2(pipex.fileout, STDOUT_FILENO);
		ft_close(pipex.fileout);
		ft_close(pipex.filein);
		execve(pipex.path, pipex.cmd, env);
		if (pipex.path)
			free(pipex.path);
		free_array(pipex.cmd);
		error(1, av, NULL);
	}
	ft_close(fd[0]);
	ft_close(pipex.fileout);
	return (wait_pid(pipex.pid, 0, pipex.k));
}
