/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/16 17:57:51 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int cmd, char *ptr, char *p)
{
	if (cmd == 3)
	{
		ft_putstr_fd("Error: can't find file1\n", 2);
		exit(1);
	}
	if (cmd == 2)
	{
		free(ptr);
		free(p);
		exit(0);
	}
	if (cmd == 1)
	{
		ft_putstr_fd("Error: cmd is incorrect\n", 2);
		exit(127);
	}
	ft_putstr_fd("Error:\n", 2);
	exit(1);
}

void heredoc(t_pipex pipex, char *p, int fd[], char **env)
{
	if (!ft_strncmp(pipex.str, p, ft_strlen(pipex.str)))
		error(2, pipex.str, p);
	ft_putstr_fd("pipe heredoc> ", 1);
	if (d_is_in(pipex.str) != 0)
		put_with_var(pipex.str, d_is_in(pipex.str) != 0, fd[1], env);
	else
		ft_putstr_fd(pipex.str, fd[1]);
}

void	here_doc(t_pipex pipex, char *av, int ac, char **env)
{
	int		fd[2];
	char	*p;

	p = ft_strjoin1(av, "\n");
	if (pipe(fd) == -1 || ac < 6)
		error(0, NULL, NULL);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
	{
		close(fd[0]);
		ft_putstr_fd("pipe heredoc> ", 1);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			heredoc(pipex, p, fd, env);
			free(pipex.str);
			pipex.str = get_next_line(0);
		}
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error(0, NULL, NULL);
	close(fd[0]);
	waitpid(pipex.pid[0], NULL, 0);
}

int	wait_pid(int *pid, int status, int cmd_num)
{
	int	i;

	i = cmd_num;
	status = 0;
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[--i], 0, 0);
	free(pid);
	return (status);
}

int	ft_pipex(t_pipex pipex)
{
	if (ft_strncmp(pipex.av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		pipex.i = 3;
		pipex.pid = malloc(sizeof(int) * (pipex.ac - pipex.i - 1));
		here_doc(pipex, pipex.av[2], pipex.ac, pipex.env);
		pipex.fileout = open(pipex.av[pipex.ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		pipex.i = 2;
		pipex.pid = malloc(sizeof(int) * (pipex.ac - pipex.i - 1));
		pipex.filein = open(pipex.av[1], O_RDONLY, 0644);
		if (pipex.filein == -1)
			error(3, NULL, NULL);
		pipex.fileout = open(pipex.av[pipex.ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(pipex.filein, STDIN_FILENO) == -1)
			error(0, NULL, NULL);
	}
	pipex.k = pipex.i - 2;
	pipex.heredoc = pipex.k;
	while (pipex.i < pipex.ac - 2)
		fork_pro(pipex.av[pipex.i++], pipex, pipex.env);
	return (last_cmd(pipex.av[pipex.ac - 2], pipex, pipex.env));
}

int	main(int ac, char *av[], char **env)
{
	int		fd[2];
	t_pipex	pipex;

	pipex.ac = ac;
	pipex.av = av;
	pipex.env = env;
	if (ac >= 5)
		return (ft_pipex(pipex));
	if (pipex.heredoc == 1)
		close(pipex.fileout);
	else
	{
		close(pipex.filein);
		close(pipex.fileout);
	}
	ft_putstr_fd("arg Error💀\n", 2);
	return (1);
}
