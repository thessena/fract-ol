/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:41:17 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 14:41:22 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <stdarg.h>
#include <stdint.h>

int	ft_handle_conv(char c, va_list *ap)
{
	if (c == 'c')
		return (ft_put_char((char)va_arg(*ap, int)));
	if (c == 's')
		return (ft_put_str(va_arg(*ap, char *)));
	if (c == 'd' || c == 'i')
		return (ft_put_signed((long)va_arg(*ap, int)));
	if (c == 'u')
		return (ft_put_unsigned_base(
				(unsigned long)va_arg(*ap, unsigned int), 10, 0));
	if (c == 'x')
		return (ft_put_unsigned_base(
				(unsigned long)va_arg(*ap, unsigned int), 16, 0));
	if (c == 'X')
		return (ft_put_unsigned_base(
				(unsigned long)va_arg(*ap, unsigned int), 16, 1));
	if (c == 'p')
		return (ft_put_ptr((uintptr_t)va_arg(*ap, void *)));
	if (c == '%')
		return (ft_put_char('%'));
	return (-1);
}
