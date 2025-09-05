/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:32:51 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 14:42:27 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <unistd.h>
#include <stdint.h>

int	ft_put_signed(long n)
{
	int	cnt;
	int	r;

	cnt = 0;
	if (n < 0)
	{
		r = ft_put_char('-');
		if (r < 0)
			return (-1);
		cnt = cnt + r;
		n = -n;
	}
	if (n >= 10)
	{
		r = ft_put_signed(n / 10);
		if (r < 0)
			return (-1);
		cnt = cnt + r;
	}
	r = ft_put_char((char)('0' + (n % 10)));
	if (r < 0)
		return (-1);
	return (cnt + r);
}

int	ft_put_unsigned_base(unsigned long n, unsigned int base, int upper)
{
	const char	*lo;
	const char	*hi;
	const char	*dig;
	int			cnt;
	int			r;

	lo = "0123456789abcdef";
	hi = "0123456789ABCDEF";
	dig = lo;
	if (upper != 0)
		dig = hi;
	cnt = 0;
	if (n >= (unsigned long)base)
	{
		r = ft_put_unsigned_base(n / base, base, upper);
		if (r < 0)
			return (-1);
		cnt = cnt + r;
	}
	r = ft_put_char(dig[n % base]);
	if (r < 0)
		return (-1);
	return (cnt + r);
}

int	ft_put_ptr(uintptr_t p)
{
	int	cnt;
	int	r;

	cnt = 0;
	r = (int)write(1, "0x", 2);
	if (r < 0)
		return (-1);
	cnt = cnt + r;
	r = ft_put_unsigned_base((unsigned long)p, 16, 0);
	if (r < 0)
		return (-1);
	return (cnt + r);
}
