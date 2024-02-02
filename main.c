/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/02 09:38:19 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	ft_printf("Error:\n");
	exit(1);
}

char	*find_path(char **env, char *cmd)
{
	char	*ptr;
	char	*str;
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		ptr = ft_strnstr(env[i], "PATH", ft_strlen("PATH"));
		if (ptr != NULL)
			break ;
		i++;
	}
	str = ft_strdup(ptr + 5);
	paths = ft_split(str, ':');
	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], '/', cmd);
		if (access(str, F_OK) == 0)
			return (str);
		free(str);
		i++;
	}
	return (NULL);
}

void	pipex(int fd[], char **av, char **env, char **cmd1, char **cmd2)
{
	char	*path1;
	char	*path2;
	int 	pid;

	path1 = find_path(env, cmd1[0]);
	path2 = find_path(env, cmd2[0]);
	pid = fork();
	if (pid < -1)
		ft_printf("Error\n");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path1, cmd1, env);
		ft_printf("%s-n/", cmd2);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
		int fd1 = open(av[4], O_WRONLY | O_CREAT , 0666);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd1, STDOUT_FILENO);
		close(fd[0]);
		execve(path2, cmd2, env);
		ft_printf("%s-n/", cmd2);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char *av[], char **env)
{
	char	**cmd1;
	char	**cmd2;
	char	*ptr;
	int		fd[2];
	char	str[BUFSIZ];

	if (ac == 5)
	{
		fd[0] = open(av[1], O_WRONLY | O_CREAT);
		fd[1] = open(av[ac - 1], O_WRONLY | O_CREAT);
		if (pipe(fd) == -1)
			error();
		cmd1 = ft_split(av[2], ' ');
		cmd2 = ft_split(av[3], ' ');
		pipex(fd, av, env, cmd1, cmd2);
	}
	else
	{
		ft_printf("Error: Bad arguments");
		ft_printf("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	}
	return (0);
}
