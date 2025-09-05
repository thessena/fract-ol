/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:32:02 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:05:06 by thessena         ###   ########.fr       */
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

static void	on_scroll(double xdelta, double ydelta, void *param)
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

static void	on_key(mlx_key_data_t kd, void *param)
{
	t_app	*app;
	double	pan;

	app = (t_app *)param;
	if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
		mlx_close_window(app->mlx);
	if (kd.action == MLX_PRESS || kd.action == MLX_REPEAT)
	{
		pan = 0.1 / app->zoom * 3.0;
		if (kd.key == MLX_KEY_LEFT || kd.key == MLX_KEY_A)
			app->center_x -= pan;
		if (kd.key == MLX_KEY_RIGHT || kd.key == MLX_KEY_D)
			app->center_x += pan;
		if (kd.key == MLX_KEY_UP || kd.key == MLX_KEY_W)
			app->center_y -= pan;
		if (kd.key == MLX_KEY_DOWN || kd.key == MLX_KEY_S)
			app->center_y += pan;
		if (kd.key == MLX_KEY_EQUAL || kd.key == MLX_KEY_KP_ADD)
			app->max_iter += 20;
		if (kd.key == MLX_KEY_MINUS || kd.key == MLX_KEY_KP_SUBTRACT)
		{
			if (app->max_iter > 20)
				app->max_iter -= 20;
		}
		if (kd.key == MLX_KEY_1)
			app->type = FRACT_MANDELBROT;
		if (kd.key == MLX_KEY_2)
			app->type = FRACT_JULIA;
		if (kd.key == MLX_KEY_3)
			app->type = FRACT_BURNING_SHIP;
		if (kd.key == MLX_KEY_C)
			app->palette = (app->palette + 1) % 3;
		if (kd.key == MLX_KEY_R)
			app_reset(app);
		render_fractal(app);
	}
}

void	setup_hooks(t_app *app)
{
	mlx_scroll_hook(app->mlx, on_scroll, app);
	mlx_key_hook(app->mlx, on_key, app);
}
