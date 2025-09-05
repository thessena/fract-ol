/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:32:02 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:45:16 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <math.h>
#include <stdint.h>

void	on_scroll(double xdelta, double ydelta, void *param);

static void	handle_pan_keys(mlx_key_data_t kd, t_app *app, double pan)
{
	if (kd.key == MLX_KEY_LEFT || kd.key == MLX_KEY_A)
		app->center_x -= pan;
	if (kd.key == MLX_KEY_RIGHT || kd.key == MLX_KEY_D)
		app->center_x += pan;
	if (kd.key == MLX_KEY_UP || kd.key == MLX_KEY_W)
		app->center_y -= pan;
	if (kd.key == MLX_KEY_DOWN || kd.key == MLX_KEY_S)
		app->center_y += pan;
}

static void	handle_mode_keys(mlx_key_data_t kd, t_app *app)
{
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
		handle_pan_keys(kd, app, pan);
		handle_mode_keys(kd, app);
		render_fractal(app);
	}
}

void	setup_hooks(t_app *app)
{
	mlx_scroll_hook(app->mlx, on_scroll, app);
	mlx_key_hook(app->mlx, on_key, app);
}
