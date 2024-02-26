/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:22:26 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/26 14:09:20 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	waitpid(pid[i--], &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (i >= 0)
		waitpid(pid[i--], 0, 0);
	free(pid);
	return (status);
}

t_pipex	fop(int flag, t_pipex p)
{
	if (flag == 1)
	{
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		p.filein = open(p.av[1], O_RDONLY, 0644);
		if (p.filein == -1)
			error(4, p.av[1], p.av[p.ac - 1]);
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p.fileout == -1)
			error(3, p.av[1], p.av[p.ac - 1]);
	}
	else if (flag == 2)
	{
		p.i++;
		p.pid = malloc(sizeof(int) * (p.ac - p.i - 1));
		p.filein = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		here_doc(p, p.av[2], p.ac, p.env);
		p.filein = open(".here_doc", O_RDONLY, 0644);
		if (p.filein == -1)
			error(4, p.av[1], p.av[p.ac - 1]);
		p.fileout = open(p.av[p.ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p.fileout == -1)
			error(3, p.av[1], p.av[p.ac - 1]);
	}
	return (p);
}

void	put_with_var(char *str, int filein, char **env)
{
	t_struct	var;

	var.i = 0;
	var.k = 0;
	while (str[var.i])
	{
		if ((str[var.i] != '$') || (str[var.i + 1] == '\0' || str[var.i
					+ 1] == ' ' || str[var.i + 1] == '\n') || (str[var.i
					+ 1] != '$'
				&& ft_isalpha(str[var.i + 1]) == 0))
			write(filein, &str[var.i++], 1);
		else
		{
			var.ptr = grep_var(str + var.i);
			var.k = ft_strlen(var.ptr);
			var.ptr1 = is_it_in(env, var.ptr);
			if (var.ptr1 != NULL)
			{
				var.ptr2 = var.ptr1 + var.k + 1;
				write(filein, var.ptr2, ft_strlen(var.ptr1) - var.k - 1);
			}
			var.i += var.k + 1;
			free(var.ptr);
		}
	}
}
