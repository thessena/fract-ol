/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:31:52 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:27:44 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <stdlib.h>

static void	app_set_defaults(t_app *app)
{
	if (!app->zoom)
		app->zoom = 1.0;
	if (!app->max_iter)
		app->max_iter = 100;
	if (app->type == FRACT_MANDELBROT)
	{
		app->center_x = -0.5;
		app->center_y = 0.0;
	}
}

static void	app_cleanup(t_app *app)
{
	if (app->img)
	{
		mlx_delete_image(app->mlx, app->img);
		app->img = NULL;
	}
	if (app->mlx)
	{
		mlx_terminate(app->mlx);
		app->mlx = NULL;
	}
}

bool	app_init(t_app *app, int w, int h, const char *title)
{
	app->width = w;
	app->height = h;
	app_set_defaults(app);
	app->mlx = mlx_init(app->width, app->height, title, true);
	if (!app->mlx)
		return (false);
	app->img = mlx_new_image(app->mlx, app->width, app->height);
	if (!app->img)
	{
		app_cleanup(app);
		return (false);
	}
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
	{
		app_cleanup(app);
		return (false);
	}
	return (true);
}

void	app_destroy(t_app *app)
{
	if (app->mlx && app->img)
	{
		mlx_delete_image(app->mlx, app->img);
		app->img = NULL;
	}
	if (app->mlx)
	{
		mlx_terminate(app->mlx);
		app->mlx = NULL;
	}
}

void	app_reset(t_app *app)
{
	app->zoom = 1.0;
	app->max_iter = 100;
	if (app->type == FRACT_MANDELBROT)
		app->center_x = -0.5;
	else
		app->center_x = 0.0;
	app->center_y = 0.0;
}
