#include "../inc/fractol.h"
#include "../mlx42/include/MLX42/MLX42.h"
#include <stdio.h>

void init_data(t_data *data)
{
	data->zoom = 1.0;
	data->moveX = -0.5;
	data->moveY = 0.0;
}

void render_fractal(t_data *data)
{
	int width = 800;
	int height = 600;
	int max_iter = 100;
	double zoom = 1.0;
	double moveX = -0.5;
	double moveY = 0.0;

	int y = 0;
	while (y < height)
	{
		int x = 0;
		while (x < width)
		{
			double pr = 1.5 * (x - width / 2) / (0.5 * zoom * width) + moveX;
			double pi = (y - height / 2) / (0.5 * zoom * height) + moveY;
			double newRe = 0, newIm = 0, oldRe, oldIm;
			int i = 0;
			
			while (i < max_iter)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + pr;
				newIm = 2 * oldRe * oldIm + pi;
				if ((newRe * newRe + newIm * newIm) > 4)
					break;
				i++;
			}

			int color = (i == max_iter) ? 0 : (i * 9) << 16 | (i * 5) << 8 | (i * 3);
			mlx_put_pixel(data->img, x, y, color << 16 | color << 8 | color);
			x++;
		}
		y++;
	}
}

void scroll_hook(double xdelta, double ydelta, void *param)
{
	(void)xdelta;

	t_data *data = (t_data *)param;
	if (ydelta > 0)
		data->zoom *= 1.1;
	else if (ydelta < 0)
		data->zoom /= 1.1;

	render_fractal(data);
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

	render_fractal(&data);
	mlx_scroll_hook(data.mlx, scroll_hook, &data);
	mlx_key_hook(data.mlx, handle_key, &data);
	mlx_loop(data.mlx);

	mlx_terminate(data.mlx);
	return (0);
}
