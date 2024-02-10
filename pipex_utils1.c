/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 15:41:40 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/10 15:54:41 by ksohail-         ###   ########.fr       */
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
	while (line[i] && line[i] != ' ')
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

void	put_with_var(char *str, int vars)
{
	char **var_tmp;
	char **var;
    int i = 0;
	if (vars == 1)
        var[0] = grep_var(str);
    else
    {
        var_tmp = ft_split(str, ' ');
        while (var[i])
            var[i] = grep_var(var_tmp[i++]);
    }
    i = 0;
    while (var[i])
        printf("var[%d]->%s-\n", i, var[i++]);
}