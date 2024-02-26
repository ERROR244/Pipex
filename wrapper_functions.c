/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:19:57 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/25 20:24:26 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int fd)
{
	int	n;

	n = close(fd);
	if (n == -1)
		exit(1);
}

int	ft_fork(void)
{
	int	n;

	n = fork();
	if (n == -1)
		exit(1);
	return (n);
}

void	ft_dup2(int fd, int std)
{
	int	n;

	n = dup2(fd, std);
	if (n == -1)
		exit(1);
}

void	error(int cmd, char *ptr, char *p)
{
	if (cmd == 4)
		ft_printf("zsh: %s: %s\n", strerror(errno), ptr);
	else if (cmd == 3)
	{
		ft_printf("zsh: %s: %s\n", strerror(errno), p);
		exit(1);
	}
	else if (cmd == 2)
	{
		free(ptr);
		free(p);
		exit(0);
	}
	else if (cmd == 1)
	{
		ft_printf("zsh: command not found: %s\n", ptr);
		exit(127);
	}
}
