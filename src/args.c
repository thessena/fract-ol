/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:01:22 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:08:06 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	print_usage(const char *prog)
{
	fprintf(stderr,
		"Usage:\n"
		"  %s mandelbrot\n"
		"  %s julia <cx> <cy>\n"
		"  %s burning\n"
		"Options:\n"
		"  --iter N       Initial max iterations (default 100)\n"
		"  --palette P    classic|fire|ocean (default classic)\n",
		prog, prog, prog);
}

static t_palette	parse_palette(const char *s)
{
	if (strcmp(s, "classic") == 0)
		return (PAL_CLASSIC);
	if (strcmp(s, "fire") == 0)
		return (PAL_FIRE);
	if (strcmp(s, "ocean") == 0)
		return (PAL_OCEAN);
	return (PAL_CLASSIC);
}

static bool	set_mode_from_args(t_app *app, int argc, char **argv)
{
	if (strcmp(argv[1], "mandelbrot") == 0)
		app->type = FRACT_MANDELBROT;
	else if (strcmp(argv[1], "julia") == 0)
	{
		app->type = FRACT_JULIA;
		if (argc < 4)
		{
			fprintf(stderr, "Error: julia requires <cx> <cy> parameters\n");
			return (false);
		}
		app->julia_cx = strtod(argv[2], NULL);
		app->julia_cy = strtod(argv[3], NULL);
	}
	else if (strcmp(argv[1], "burning") == 0)
		app->type = FRACT_BURNING_SHIP;
	else
	{
		fprintf(stderr, "Error: unknown fractal '%s'\n", argv[1]);
		return (false);
	}
	return (true);
}

static void	parse_options(t_app *app, int argc, char **argv, int start)
{
	int	i;

	i = start;
	while (i < argc)
	{
		if (strcmp(argv[i], "--iter") == 0 && i + 1 < argc)
		{
			i++;
			app->max_iter = (int)strtol(argv[i], NULL, 10);
			if (app->max_iter < 10)
				app->max_iter = 10;
		}
		else if (strcmp(argv[i], "--palette") == 0 && i + 1 < argc)
		{
			i++;
			app->palette = parse_palette(argv[i]);
		}
		i++;
	}
}

bool	parse_args(t_app *app, int argc, char **argv)
{
	memset(app, 0, sizeof(*app));
	app->zoom = 1.0;
	app->palette = PAL_CLASSIC;
	if (argc < 2)
	{
		print_usage(argv[0]);
		return (false);
	}
	if (!set_mode_from_args(app, argc, argv))
	{
		print_usage(argv[0]);
		return (false);
	}
	parse_options(app, argc, argv, 2);
	return (true);
}
