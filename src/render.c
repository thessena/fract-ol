/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:58:24 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:04:38 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>

static int	mandelbrot(t_cpx c, int max_iter)
{
	double	zr;
	double	zi;
	double	zr2;
	int		i;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i < max_iter)
	{
		zr2 = zr * zr - zi * zi + c.re;
		zi = 2.0 * zr * zi + c.im;
		zr = zr2;
		if (zr * zr + zi * zi > 4.0)
			break ;
		i++;
	}
	return (i);
}

static int	julia(t_cpx z, t_cpx c, int max_iter)
{
	double	zr2;
	int		i;

	i = 0;
	while (i < max_iter)
	{
		zr2 = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = zr2;
		if (z.re * z.re + z.im * z.im > 4.0)
			break ;
		i++;
	}
	return (i);
}

static int	burning_ship(t_cpx c, int max_iter)
{
	double	zr;
	double	zi;
	double	azr;
	double	azi;
	double	zr2;
	int		i;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i < max_iter)
	{
		azr = fabs(zr);
		azi = fabs(zi);
		zr2 = azr * azr - azi * azi + c.re;
		zi = 2.0 * azr * azi + c.im;
		zr = zr2;
		if (zr * zr + zi * zi > 4.0)
			break ;
		i++;
	}
	return (i);
}

static void	draw_pixel(t_app *app, int x, int y, double scale, t_cpx jc)
{
	t_cpx		p;
	int			iter;
	uint32_t	col;

	p.re = app->center_x + (x - app->width * 0.5) * scale;
	p.im = app->center_y + (y - app->height * 0.5) * scale;
	if (app->type == FRACT_MANDELBROT)
		iter = mandelbrot(p, app->max_iter);
	else if (app->type == FRACT_JULIA)
		iter = julia(p, jc, app->max_iter);
	else
		iter = burning_ship(p, app->max_iter);
	if (iter >= app->max_iter)
		col = pack_rgba(0, 0, 0, 255);
	else
		col = palette_color(app,
				(double)iter / (double)app->max_iter);
	mlx_put_pixel(app->img, x, y, col);
}

void	render_fractal(t_app *app)
{
	int		y;
	int		x;
	double	scale;
	t_cpx	jc;

	scale = 3.0 / (double)app->height;
	scale /= app->zoom;
	jc.re = app->julia_cx;
	jc.im = app->julia_cy;
	y = 0;
	while (y < app->height)
	{
		x = 0;
		while (x < app->width)
		{
			draw_pixel(app, x, y, scale, jc);
			x++;
		}
		y++;
	}
}
