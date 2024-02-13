/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/13 10:32:04 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int cmd)
{
	if (cmd == 1)
	{
		ft_putstr_fd("Error: cmd is incorrect\n", 2);
		exit(127);
	}
	ft_putstr_fd("Error:\n", 2);
	exit(1);
}

void	last_cmd(char *av, t_pipex pipex, char **env)
{
	*pipex.pid = fork();
	if (*pipex.pid == 0)
	{
		dup2(pipex.fileout, STDOUT_FILENO);
		pipex.cmd = ft_split(av, ' ');
		pipex.path = find_path(env, pipex.cmd[0], pipex);
		execve(pipex.path, pipex.cmd, env);
		if (pipex.path)
			free(pipex.path);
		free_array(pipex.cmd);
		close(pipex.fileout);
		error(1);
	}
	
}

void	here_doc(t_pipex pipex, char *av, int ac, char **env)
{
	int	fd[2];
	char *p = ft_strjoin1(av, "\n");
	int	k;

	if (ac < 6)
		error(0);
	if (pipe(fd) == -1)
		error(0);
	*pipex.pid = fork();
	if (*pipex.pid == 0)
	{
		close(fd[0]);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			if (!ft_strncmp(pipex.str, p, ft_strlen(pipex.str)))
			{
				free(pipex.str);
				exit(0);
			}
			k = d_is_in(pipex.str);
			if (k != 0)
				put_with_var(pipex.str, k, fd[1], env);
			else
				ft_putstr_fd(pipex.str, fd[1]);
			free(pipex.str);
			pipex.str = get_next_line(0);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(*pipex.pid, NULL, 0);
		pipex.pid++;
	}
}

int	wait_pid(int *pid, int status, int cmd_num)
{
	int i = cmd_num - 1;

	status = 0;
	printf("//////////////////!!!//////////////////\n");
	while (i >= 0)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child process PID: %d\n", pid[i]);
			status = WEXITSTATUS(status);
			break;
		}
		i--;
	}
	while (i >= 0)
		waitpid(pid[--i], 0, 0);
	free(pid);
	// int i;

	// i = 0;
	// status = 0;
	// while (i < cmd_num)
	// {
	// 	waitpid(pid[i], &status, 0);
	// 	if (WIFEXITED(status))
	// 		status = WEXITSTATUS(status);
	// 	i++;
	// }
	// printf("%d-\n", i);
	return (status);
}

int	main(int ac, char *av[], char **env)
{
	int		fd[2];
	int		cmd_num;
	int		status;
	t_pipex	pipex;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0)
		{
			pipex.i = 3;
			cmd_num = ac - pipex.i - 1;
			pipex.pid = malloc(sizeof(int) * (cmd_num));
			pipex.fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			here_doc(pipex, av[2], ac, env);
		}
		else
		{
			pipex.i = 2;
			cmd_num = ac - pipex.i - 1;
			pipex.pid = malloc(sizeof(int) * (cmd_num));
			pipex.filein = open(av[1], O_RDONLY, 0777);
			pipex.fileout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(pipex.filein, STDIN_FILENO);
		}
		while (pipex.i < ac - 2)
			fork_pro(av[pipex.i++], pipex, env);
		last_cmd(av[ac - 2], pipex, env);
		status = wait_pid(pipex.pid, status, cmd_num);
	}
	else
		ft_putstr_fd("arg Error💀->Ex: \n-./pipex file1 cmd1 cmd file2\n-./pipex here_doc LIMITER cmd cmd1 file\n", 2);
	return (status);
}
