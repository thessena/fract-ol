/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:37:05 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:40:49 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>

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
