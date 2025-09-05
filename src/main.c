/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:31:36 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 13:25:57 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
#include <stdio.h>

static void	on_close(void *param)
{
	(void)param;
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (!parse_args(&app, argc, argv))
		return (1);
	if (!app_init(&app, 1000, 800, "fract-ol"))
		return (1);
	render_fractal(&app);
	setup_hooks(&app);
	mlx_close_hook(app.mlx, on_close, &app);
	mlx_loop(app.mlx);
	app_destroy(&app);
	return (0);
}
