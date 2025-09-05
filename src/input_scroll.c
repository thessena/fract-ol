/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:42:25 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:47:38 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>
#include <stdint.h>

static void	pixel_to_complex_local(t_app *app, int x, int y, t_cpx *out)
{
	double	scale;

	scale = 3.0 / (double)app->height;
	scale /= app->zoom;
	out->re = app->center_x + (x - app->width * 0.5) * scale;
	out->im = app->center_y + (y - app->height * 0.5) * scale;
}

static void	zoom_at(t_app *app, double mouse_x, double mouse_y, double factor)
{
	t_cpx	before;
	t_cpx	after;

	pixel_to_complex_local(app, (int)mouse_x, (int)mouse_y, &before);
	app->zoom *= factor;
	pixel_to_complex_local(app, (int)mouse_x, (int)mouse_y, &after);
	app->center_x += (before.re - after.re);
	app->center_y += (before.im - after.im);
}

void	on_scroll(double xdelta, double ydelta, void *param)
{
	t_app	*app;
	int32_t	mx_i;
	int32_t	my_i;
	double	mx;
	double	my;

	(void)xdelta;
	app = (t_app *)param;
	mx_i = 0;
	my_i = 0;
	mlx_get_mouse_pos(app->mlx, &mx_i, &my_i);
	mx = (double)mx_i;
	my = (double)my_i;
	if (ydelta > 0)
		zoom_at(app, mx, my, 1.2);
	else if (ydelta < 0)
		zoom_at(app, mx, my, 1.0 / 1.2);
	render_fractal(app);
}
