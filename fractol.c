/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:24:35 by thessena          #+#    #+#             */
/*   Updated: 2025/02/01 14:03:31 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/MLX42/include/MLX42/MLX42.h"

#define WIDTH 800
#define HEIGHT 800

int	main(void)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
