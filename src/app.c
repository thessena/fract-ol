#include "../inc/fractol.h"
#include <stdlib.h>

bool app_init(t_app *app, int w, int h, const char *title)
{
    app->width = w;
    app->height = h;
    if (!app->zoom)
        app->zoom = 1.0;
    if (!app->max_iter)
        app->max_iter = 100;
    if (app->type == FRACT_MANDELBROT)
    {
        app->center_x = -0.5;
        app->center_y = 0.0;
    }
    app->mlx = mlx_init(app->width, app->height, title, true);
    if (!app->mlx)
        return false;
    app->img = mlx_new_image(app->mlx, app->width, app->height);
    if (!app->img)
        goto fail;
    if (mlx_image_to_window(app->mlx, app->img, 0, 0) < 0)
        goto fail;
    return true;

fail:
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
    return false;
}

void app_destroy(t_app *app)
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

void app_reset(t_app *app)
{
    app->zoom = 1.0;
    app->max_iter = 100;
    app->center_x = (app->type == FRACT_MANDELBROT) ? -0.5 : 0.0;
    app->center_y = 0.0;
}
