/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:35:05 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/01 21:48:50 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strchr(const char *s, int c)
{
	char	k;

	k = (char)c;
	while (*s)
	{
		if (*s == k)
			return ((char *)s);
		s++;
	}
	if (k == '\0')
		return ((char *)s);
	return (NULL);
}
