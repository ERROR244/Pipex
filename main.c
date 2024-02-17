/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/17 15:41:32 by ksohail-         ###   ########.fr       */
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
		ft_putstr_fd("Error: cmmd is incorrect\n", 2);
		exit(127);
	}
	ft_putstr_fd("Error:\n", 2);
	exit(1);
}

void	heredoc(t_pipex pipex, char *p, int fd[], char **env)
{
	if (!ft_strncmp(pipex.str, p, ft_strlen(pipex.str)))
		error(2, pipex.str, p);
	ft_putstr_fd("pipe heredoc> ", 1);
	if (d_is_in(pipex.str) != 0)
		put_with_var(pipex.str, d_is_in(pipex.str) != 0, fd[1], env);
	else
		ft_putstr_fd(pipex.str, fd[1]);
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

int	ft_pipex(t_pipex p)
{
	if (ft_strncmp(p.av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		p.i = 3;
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		here_doc(p, p.av[2], p.ac, p.env);
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		p.i = 2;
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		p.filein = open(p.av[1], O_RDONLY, 0644);
		if (p.filein == -1)
			error(3, NULL, NULL);
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(p.filein, STDIN_FILENO) == -1)
			error(0, NULL, NULL);
	}
	p.k = p.i - 2;
	p.heredoc = p.k;
	while (p.i < p.ac - 2)
		fork_pro(p.av[p.i++], p, p.k++);
	return (last_cmd(p.av[p.ac - 2], p, p.env));
}

int	main(int ac, char *av[], char **env)
{
	int		status;
	t_pipex	pipex;

	status = 1;
	pipex.ac = ac;
	pipex.av = av;
	pipex.env = env;
	if (ac >= 5)
		status = ft_pipex(pipex);
	else
		ft_putstr_fd("arg Error💀\n", 2);
	if (pipex.heredoc == 1)
		close(pipex.fileout);
	else
	{
		close(pipex.filein);
		close(pipex.fileout);
	}
	return (status);
}
