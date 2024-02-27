/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:41:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/27 17:16:44 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*touppercase(char *str)
{
	char	*ptr;
	int		i;
	int		k;

	if (ft_strlen(str) == 0)
		return (str);
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
	j = ++i;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	k = i - j;
	str = malloc(sizeof(char) * (k + 1));
	if (!str)
		return (NULL);
	while (l < k)
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
	return (k);
}

void	here_doc(t_pipex pipex)
{
	char	*p;

	pipex.k++;
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
	{
		p = ft_strjoin1(pipex.av[2], "\n");
		ft_putstr_fd("pipe pipe heredoc> ", 1);
		pipex.str = get_next_line(0);
		while (pipex.str)
		{
			heredoc(pipex, p, pipex.env);
			free(pipex.str);
			ft_putstr_fd("pipe pipe heredoc> ", 1);
			pipex.str = get_next_line(0);
		}
		free(p);
		exit(0);
	}
	ft_close(pipex.filein);
	waitpid(pipex.pid[0], NULL, 0);
}
