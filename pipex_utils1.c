/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:41:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/15 18:57:26 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	str = malloc(sizeof(char) * k);
	while (l < k)
		str[l++] = line[j++];
	str[l] = '\0';
	return (str);
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

void	put_with_var(char *str, int vars, int fd, char **env)
{
	int		i;
	int		k;
	char	*ptr;
	char	*ptr1;
	char	*ptr2;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != '$')
			write(fd, &str[i], 1);
		else
		{
			ptr = grep_var(str + i);
			k = ft_strlen(ptr);
			ptr1 = is_it_in(env, ptr);
			if (ptr1 != NULL)
			{
				ptr2 = ptr1 + k + 1;
				write(fd, ptr2, ft_strlen(ptr1) - k - 1);
				i += k;
			}
			else
				i += k;
			free(ptr);
		}
		i++;
	}
}
