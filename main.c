/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/24 17:22:17 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex(t_pipex p, int fd[2])
{
	if (ft_strncmp(p.av[1], "here_doc", ft_strlen("here_doc")) == 0)
		p = fop(2, p);
	else
		p = fop(1, p);
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
	pipex.k = 0;
	if (ac >= 5)
		status = ft_pipex(pipex, fd);
	else
		ft_putstr_fd("arg Error💀\n", 2);
	close(pipex.filein);
	close(pipex.fileout);
	unlink("here_doc");
	return (status);
}
