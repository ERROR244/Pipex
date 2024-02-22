/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:41:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/22 18:37:06 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*touppercase(char *str)
{
	char	*ptr;
	int		i;
	int		k;

	ptr = str;
	i = ft_isalpha(*ptr);
	ptr++;
	while (*ptr)
	{
		k = ft_isalpha(*ptr);
		if (i != k)
			return (str);
		ptr++;
	}
	ptr = str;
	while (*ptr)
	{
		*ptr = ft_toupper(*ptr);
		ptr++;
	}
	return (str);
}

char	*grep_var(char *line)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i - 1] != '$')
		i++;
	j = i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	k = i - j;
	str = malloc(sizeof(char) * (k));
	while (l < (k))
		str[l++] = line[j++];
	str[l] = '\0';
	return (touppercase(str));
}

int	d_is_in(char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '$')
			k++;
		i++;
	}
	return (1);
}

void	put_with_var(char *str, int filein, char **env)
{
	t_struct	var;

	var.i = 0;
	var.k = 0;
	while (str[var.i])
	{
		if (str[var.i] != '$')
			write(filein, &str[var.i], 1);
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
			var.i += var.k;
			free(var.ptr);
		}
		var.i++;
	}
}

void	here_doc(t_pipex pipex, char *av, int ac, char **env)
{
	char	*p;

	if (ac < 6)
		exit(errno);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
	{
		p = ft_strjoin1(av, "\n");
		ft_putstr_fd("pipe heredoc> ", 1);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			heredoc(pipex, p, env);
			free(pipex.str);
			pipex.str = get_next_line(0);
		}
	}
	close(pipex.filein);
	waitpid(pipex.pid[0], NULL, 0);
}
