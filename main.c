/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/10 15:54:52 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int cmd)
{
	if (cmd == 1)
	{
		ft_putstr_fd("Error: cmd is incorrect\n", 2);
		exit(1);
	}
	ft_putstr_fd("Error:\n", 2);
	exit(1);
}

void	last_cmd(char *av, t_pipex pipex, char **env)
{
	dup2(pipex.fileout, STDOUT_FILENO);
	pipex.cmd = ft_split(av, ' ');
	pipex.path = find_path(env, pipex.cmd[0], pipex);
	execve(pipex.path, pipex.cmd, env);
	if (pipex.path)
		free(pipex.path);
	ft_putstr_fd("Error: cmd is incorrect\n", 2);
	free_array(pipex.cmd);
	close(pipex.fileout);
}

void	here_doc(t_pipex pipex, char *av, int ac, char **env)
{
	int	fd[2];
	int	k;

	if (ac < 6)
		error(0);
	if (pipe(fd) == -1)
		error(0);
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		close(fd[0]);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			if (!ft_strncmp(pipex.str, av, ft_strlen(pipex.str)))
			{
				free(pipex.str);
				exit(0);
			}
			k = d_is_in(pipex.str);
			// if (k != 0)
				put_with_var(pipex.str, k);
			// else
				ft_putstr_fd(pipex.str, fd[1]);
			free(pipex.str);
			pipex.str = get_next_line(0);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(0, NULL, 0);
	}
}

int	main(int ac, char *av[], char **env)
{
	int		fd[2];
	t_pipex	pipex;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			pipex.i = 3;
			pipex.fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND,
					0777);
			here_doc(pipex, av[2], ac, env);
		}
		else
		{
			pipex.i = 2;
			pipex.filein = open(av[1], O_RDONLY, 0777);
			pipex.fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC,
					0777);
			dup2(pipex.filein, STDIN_FILENO);
		}
		while (pipex.i < ac - 2)
			fork_pro(av[pipex.i++], pipex, env);
		last_cmd(av[ac - 2], pipex, env);
	}
	else
		ft_putstr_fd("arg Error💀->Ex: \n-./pipex file1 cmd1 cmd file2\n-./pipex here_doc LIMITER cmd cmd1 file\n",
			2);
	return (0);
}
