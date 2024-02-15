/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/15 19:00:04 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int cmd, char *ptr)
{
	if (cmd == 2)
	{
		free(ptr);
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

void	here_doc(t_pipex pipex, char *av, int ac, char **env)
{
	int		fd[2];
	char	*p;

	p = ft_strjoin1(av, "\n");
	if (pipe(fd) == -1 || ac < 6)
		error(0, NULL);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
	{
		close(fd[0]);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			if (!ft_strncmp(pipex.str, p, ft_strlen(pipex.str)))
				error(2, pipex.str);
			if (d_is_in(pipex.str) != 0)
				put_with_var(pipex.str, d_is_in(pipex.str) != 0, fd[1], env);
			else
				ft_putstr_fd(pipex.str, fd[1]);
			free(pipex.str);
			pipex.str = get_next_line(0);
		}
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pipex.pid[0], NULL, 0);
}

int	wait_pid(int *pid, int status, int cmd_num)
{
	int	i;

	i = cmd_num;
	status = 0;
	while (i >= 0)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			break ;
		}
		i--;
	}
	while (i >= 0)
		waitpid(pid[--i], NULL, 0);
	free(pid);
	return (status);
}

int	ft_pipex(t_pipex pipex)
{
	if (ft_strncmp(pipex.av[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		pipex.k = 1;
		pipex.i = 3;
		pipex.pid = malloc(sizeof(int) * (pipex.ac - pipex.i - 1));
		pipex.fileout = open(pipex.av[pipex.ac - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc(pipex, pipex.av[2], pipex.ac, pipex.env);
	}
	else
	{
		pipex.k = 0;
		pipex.i = 2;
		pipex.pid = malloc(sizeof(int) * (pipex.ac - pipex.i - 1));
		pipex.filein = open(pipex.av[1], O_RDONLY, 0644);
		pipex.fileout = open(pipex.av[pipex.ac - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(pipex.filein, STDIN_FILENO);
	}
	while (pipex.i < pipex.ac - 2)
	{
		fork_pro(pipex.av[pipex.i++], pipex, pipex.env);
		pipex.k++;
	}
	last_cmd(pipex.av[pipex.ac - 2], pipex, pipex.env);
	return (wait_pid(pipex.pid, 0, pipex.k));
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
	ft_putstr_fd("arg Error💀\n", 2);
	return (1);
}
