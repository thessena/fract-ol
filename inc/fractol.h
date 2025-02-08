#ifndef FRACTOL_H
# define FRACTOL_H

#include "../mlx42/include/MLX42/MLX42.h"

typedef struct s_data
{
    mlx_t *mlx;
    mlx_image_t *img;
} t_data;

void	render_fractal(t_data *data);
void	handle_events(t_data *data);

#endif
