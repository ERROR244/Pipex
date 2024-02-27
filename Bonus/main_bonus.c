/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/27 14:38:52 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_pipex_bonus(t_pipex pipex, int fd[2])
{
	if (pipex.here_doc == 0)
		pipex = fop(2, pipex, fd);
	else
		pipex = fop(1, pipex, fd);
	while (pipex.i < pipex.ac - 2)
	{
		if (pipe(fd) == -1)
			exit(errno);
		fork_pro(pipex.av[pipex.i++], pipex, pipex.k++, fd);
		pipex.filein = fd[0];
	}
	return (last_cmd(pipex.av[pipex.ac - 2], pipex, pipex.env, fd));
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
	pipex.here_doc = ft_strcmp(pipex.av[1], "here_doc");
	pipex.k = 0;
	if ((ac >= 5 && pipex.here_doc != 0) || (pipex.ac >= 6 && pipex.here_doc == 0))
		status = ft_pipex_bonus(pipex, fd);
	else
	{
		ft_putstr_fd("arg Error💀\n", 2);
		exit(1);
	}
	close(pipex.filein);
	return (status);
}
