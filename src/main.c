#include "../inc/fractol.h"
#include "../mlx42/include/MLX42/MLX42.h"
#include <stdio.h>

void render_fractal(t_data *data)
{
	int width = 800;
	int height = 600;
	int max_iter = 100;
	double zoom = 1.0;
	double moveX = -0.5;
	double moveY = 0.0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			double pr = 1.5 * (x - width / 2) / (0.5 * zoom * width) + moveX;
			double pi = (y - height / 2) / (0.5 * zoom * height) + moveY;
			double newRe = 0, newIm = 0, oldRe, oldIm;
			int i;
			for (i = 0; i < max_iter; i++)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + pr;
				newIm = 2 * oldRe * oldIm + pi;
				if ((newRe * newRe + newIm * newIm) > 4) break;
			}
			int color = (i == max_iter) ? 0 : (i * 255 / max_iter);
			mlx_put_pixel(data->img, x, y, color << 16 | color << 8 | color);
		}
	}
}

void handle_key(mlx_key_data_t keydata, void *param)
{
	t_data *data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(data->mlx);
	}
}

int main(void)
{
	t_data data;

	data.mlx = mlx_init(800, 600, "Fract-ol", true);
	if (!data.mlx)
	{
		printf("Error: mlx_init failed\n");
		return (1);
	}
	data.img = mlx_new_image(data.mlx, 800, 600);
	mlx_image_to_window(data.mlx, data.img, 0, 0);

	mlx_key_hook(data.mlx, handle_key, &data);
	while(1)
	{
		render_fractal(&data);
		mlx_loop(data.mlx);
	}
	mlx_terminate(data.mlx);
	return (0);
}
