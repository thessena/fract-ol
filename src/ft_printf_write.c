/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:45 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 14:44:26 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <unistd.h>

int	ft_put_char(char c)
{
	ssize_t	w;

	w = write(1, &c, 1);
	if (w < 0)
		return (-1);
	return ((int)w);
}

int	ft_put_str(const char *s)
{
	int		i;
	int		r;

	if (s == 0)
		return ((int)write(1, "(null)", 6));
	i = 0;
	while (s[i] != '\0')
	{
		r = (int)write(1, &s[i], 1);
		if (r < 0)
			return (-1);
		i = i + 1;
	}
	return (i);
}
