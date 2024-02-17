/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:43:02 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/17 15:35:03 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	k;

	ptr = (unsigned char *)s;
	k = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == k)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}
