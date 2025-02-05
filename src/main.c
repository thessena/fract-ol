#include "../inc/fractol.h"
#include "../libs/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

int main(void)
{
    t_data data;

	printf("Pimmelbus\n");
	data.mlx = mlx_init(800, 600, "Fract-ol", true);
    if (!data.mlx)
    {
	printf("Pimmelbus ERROR mit dem MLX");
        return (1);
    }
    data.img = mlx_new_image(data.mlx, 800, 600);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	printf("Pimmelbus mlx_loop\n");
    mlx_loop(data.mlx);
    return (0);
}
