/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksohail- <ksohail-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:17:54 by ksohail-          #+#    #+#             */
/*   Updated: 2024/02/01 21:48:50 by ksohail-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd >= 0 && s != NULL)
	{
		while (*s)
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}
