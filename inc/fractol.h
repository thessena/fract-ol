#ifndef FRACTOL_H
# define FRACTOL_H

#include "../libs/MLX42/include/MLX42/MLX42.h"

typedef struct s_data
{
    mlx_t *mlx;
    mlx_image_t *img;
    double min_re;
    double max_re;
    double min_im;
    double max_im;
    int max_iter;
} t_data;

#endif
