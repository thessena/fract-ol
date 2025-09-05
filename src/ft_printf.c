/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:08 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 14:45:55 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

static int	ft_write_and_advance(const char **fmt, int *total)
{
	int	w;

	w = (int)write(1, *fmt, 1);
	if (w < 0)
		return (-1);
	*total = *total + 1;
	*fmt = *fmt + 1;
	return (1);
}

static int	ft_handle_percent(const char **fmt, va_list *ap, int *total)
{
	int	n;

	if (**fmt == '\0')
		return (1);
	n = ft_handle_conv(**fmt, ap);
	if (n < 0)
		return (-1);
	*total = *total + n;
	*fmt = *fmt + 1;
	return (1);
}

static int	ft_printf_loop(const char *fmt, va_list *ap)
{
	int	total;
	int	ok;

	total = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt = fmt + 1;
			ok = ft_handle_percent(&fmt, ap, &total);
			if (ok < 0)
				return (-1);
		}
		else
		{
			ok = ft_write_and_advance(&fmt, &total);
			if (ok < 0)
				return (-1);
		}
	}
	return (total);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, fmt);
	res = ft_printf_loop(fmt, &ap);
	va_end(ap);
	return (res);
}
