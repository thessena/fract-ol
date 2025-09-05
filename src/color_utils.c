/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:00:29 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:47:59 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

static t_rgba	unpack(uint32_t c)
{
	t_rgba	v;

	v.a = (c >> 24) & 0xFF;
	v.r = (c >> 16) & 0xFF;
	v.g = (c >> 8) & 0xFF;
	v.b = c & 0xFF;
	return (v);
}

static uint8_t	lerp8(uint8_t x, uint8_t y, double t)
{
	return ((uint8_t)(x + (y - x) * t));
}

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)a << 24)
		| ((uint32_t)r << 16)
		| ((uint32_t)g << 8)
		| (uint32_t)b);
}

uint32_t	lerp_color(uint32_t c1, uint32_t c2, double t)
{
	t_rgba	u;
	t_rgba	v;
	t_rgba	w;

	u = unpack(c1);
	v = unpack(c2);
	w.a = lerp8(u.a, v.a, t);
	w.r = lerp8(u.r, v.r, t);
	w.g = lerp8(u.g, v.g, t);
	w.b = lerp8(u.b, v.b, t);
	return (pack_rgba(w.r, w.g, w.b, w.a));
}
