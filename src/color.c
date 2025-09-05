/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:00:29 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:27:35 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>

uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (((uint32_t)a << 24)
		| ((uint32_t)r << 16)
		| ((uint32_t)g << 8)
		| (uint32_t)b);
}

typedef struct s_rgba
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}t_rgba;

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

static uint32_t	lerp_color(uint32_t c1, uint32_t c2, double t)
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

static uint32_t	palette_fire(double t)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;

	a = pack_rgba(0, 0, 0, 255);
	b = pack_rgba(255, 80, 0, 255);
	c = pack_rgba(255, 255, 0, 255);
	if (t < 0.5)
		return (lerp_color(a, b, t * 2.0));
	return (lerp_color(b, c, (t - 0.5) * 2.0));
}

static uint32_t	palette_ocean(double t)
{
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;

	a = pack_rgba(0, 7, 100, 255);
	b = pack_rgba(32, 107, 203, 255);
	c = pack_rgba(237, 255, 255, 255);
	if (t < 0.5)
		return (lerp_color(a, b, t * 2.0));
	return (lerp_color(b, c, (t - 0.5) * 2.0));
}

uint32_t	palette_color(t_app *app, double t)
{
	uint32_t	a;
	uint32_t	b;

	if (t < 0)
		t = 0;
	if (t > 1)
		t = 1;
	if (app->palette == PAL_FIRE)
		return (palette_fire(t));
	if (app->palette == PAL_OCEAN)
		return (palette_ocean(t));
	a = pack_rgba(0, 0, 0, 255);
	b = pack_rgba(255, 255, 255, 255);
	return (lerp_color(a, b, t));
}
