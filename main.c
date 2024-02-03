/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/03 01:54:54 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int fd[], char **av, char **env)
{
	t_pipex	pipex;

	pipex.pid = fork();
	if (pipex.pid == -1)
		error();
	else if (pipex.pid == 0)
		child(av, fd, pipex, env);
	else
		parent(av, fd, pipex, env);
}

int	main(int ac, char *av[], char **env)
{
	char	*ptr;
	int		fd[2];

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			error();
		pipex(fd, av, env);
	}
	else
	{
		ft_putstr_fd("arguments Error-->", 2);
		ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 file2\n", 2);
	}
	return (0);
}
