/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/27 17:41:00 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_pid(int *pid, int status, int cmd_num)
{
	int	i;

	i = cmd_num;
	status = 0;
	waitpid(pid[i--], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	free(pid);
	return (status);
}

int	ft_pipex(t_pipex p, int fd[2])
{
	p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
	p.filein = open(p.av[1], O_RDONLY, 0644);
	if (p.filein == -1)
		error(4, p.av[1], p.av[p.ac - 1]);
	p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p.fileout == -1)
		error(3, p.av[1], p.av[p.ac - 1]);
	if (pipe(fd) == -1)
		exit(errno);
	fork_pro(p.av[p.i++], p, p.k++, fd);
	p.filein = fd[0];
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
	pipex.k = 0;
	if (ac == 5)
		status = ft_pipex(pipex, fd);
	else
	{
		ft_putstr_fd("arg Error💀\n", 2);
		exit(1);
	}
	ft_close(pipex.filein);
	return (status);
}
