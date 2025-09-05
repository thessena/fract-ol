/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:31:45 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:13:48 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdint.h>
#include <stdbool.h>
#include "../mlx42/include/MLX42/MLX42.h"

typedef struct s_cpx
{
	double	re;
	double	im;
}	t_cpx;

typedef enum e_fractal
{
	FRACT_MANDELBROT = 0,
	FRACT_JULIA = 1,
	FRACT_BURNING_SHIP = 2
}	t_fractal;

typedef enum e_palette
{
	PAL_CLASSIC = 0,
	PAL_FIRE = 1,
	PAL_OCEAN = 2
}	t_palette;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	double		center_x;
	double		center_y;
	double		zoom;
	int			max_iter;
	t_fractal	type;
	double		julia_cx;
	double		julia_cy;
	bool		julia_lock;
	t_palette	palette;
}	t_app;

// app.c
bool	app_init(t_app *app, int w, int h, const char *title);
void	app_destroy(t_app *app);
void	app_reset(t_app *app);

// args.c
bool	parse_args(t_app *app, int argc, char **argv);
void	print_usage(const char *prog);

// render.c
void	render_fractal(t_app *app);

// input.c
void	setup_hooks(t_app *app);

// color.c
uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t palette_color(t_app *app, double t);

#endif
