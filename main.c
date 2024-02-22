/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/22 17:59:56 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int cmd, char *ptr, char *p)
{
	if (cmd == 3)
	{
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}
	else if (cmd == 2)
	{
		free(ptr);
		free(p);
		exit(0);
	}
	else if (cmd == 1)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
}

void	heredoc(t_pipex pipex, char *p, char **env)
{
	if (!ft_strncmp(pipex.str, p, ft_strlen(pipex.str)))
		error(2, pipex.str, p);
	ft_putstr_fd("pipe heredoc> ", 1);
	if (d_is_in(pipex.str) != 0)
		put_with_var(pipex.str, pipex.filein, env);
	else
		ft_putstr_fd(pipex.str, pipex.filein);
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

int	ft_pipex(t_pipex p, int fd[2])
{
	if (ft_strncmp(p.av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		p.i++;
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		p.filein = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc(p, p.av[2], p.ac, p.env);
	}
	else
	{
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p.filein == -1)
			error(3, p.av[1], NULL);
	}
	p.filein = open(p.av[1], O_RDONLY, 0644);
	p.k = p.i - 2;
	while (p.i < p.ac - 2)
	{
		if (pipe(fd) == -1)
			exit(errno);
		fork_pro(p.av[p.i++], p, p.k++, fd);
		p.filein = fd[0];
	}
	return (last_cmd(p.av[p.ac - 2], p, p.env, fd));
}

int	main(int ac, char *av[], char **env)
{
	t_pipex	pipex;
	int		status;
	int		fd[2];

	status = 1;
	pipex.ac = ac;
	pipex.av = av;
	pipex.env = env;
	pipex.i = 2;
	if (ac >= 5)
		status = ft_pipex(pipex, fd);
	else
		ft_putstr_fd("arg Error💀\n", 2);
	close(pipex.filein);
	close(pipex.fileout);
	unlink("here_doc");
	return (status);
}
