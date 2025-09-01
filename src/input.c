#include "../inc/fractol.h"
#include <math.h>
#include <stdint.h>

static void pixel_to_complex_local(t_app *app, int x, int y, double *out_r, double *out_i)
{
    double scale = 3.0 / (double)app->height;
    scale /= app->zoom;
    *out_r = app->center_x + (x - app->width * 0.5) * scale;
    *out_i = app->center_y + (y - app->height * 0.5) * scale;
}

static void zoom_at(t_app *app, double mouse_x, double mouse_y, double factor)
{
    double before_r, before_i;
    double after_r, after_i;
    double prev_zoom = app->zoom;
    pixel_to_complex_local(app, (int)mouse_x, (int)mouse_y, &before_r, &before_i);
    app->zoom *= factor;
    pixel_to_complex_local(app, (int)mouse_x, (int)mouse_y, &after_r, &after_i);
    app->center_x += (before_r - after_r);
    app->center_y += (before_i - after_i);
    (void)prev_zoom;
}

static void on_scroll(double xdelta, double ydelta, void *param)
{
    (void)xdelta;
    t_app *app = (t_app*)param;
    int32_t mx_i = 0, my_i = 0;
    mlx_get_mouse_pos(app->mlx, &mx_i, &my_i);
    double mx = (double)mx_i;
    double my = (double)my_i;
    if (ydelta > 0)
        zoom_at(app, mx, my, 1.2);
    else if (ydelta < 0)
        zoom_at(app, mx, my, 1.0/1.2);
    render_fractal(app);
}

static void on_key(mlx_key_data_t kd, void *param)
{
    t_app *app = (t_app*)param;
    if (kd.key == MLX_KEY_ESCAPE && kd.action == MLX_PRESS)
        mlx_close_window(app->mlx);
    if (kd.action == MLX_PRESS || kd.action == MLX_REPEAT)
    {
        double pan = 0.1 / app->zoom * 3.0;
        if (kd.key == MLX_KEY_LEFT || kd.key == MLX_KEY_A) app->center_x -= pan;
        if (kd.key == MLX_KEY_RIGHT || kd.key == MLX_KEY_D) app->center_x += pan;
        if (kd.key == MLX_KEY_UP || kd.key == MLX_KEY_W) app->center_y -= pan;
        if (kd.key == MLX_KEY_DOWN || kd.key == MLX_KEY_S) app->center_y += pan;
        if (kd.key == MLX_KEY_EQUAL || kd.key == MLX_KEY_KP_ADD) app->max_iter += 20;
        if (kd.key == MLX_KEY_MINUS || kd.key == MLX_KEY_KP_SUBTRACT) app->max_iter = (app->max_iter>20)? app->max_iter-20: app->max_iter;
        if (kd.key == MLX_KEY_1) app->type = FRACT_MANDELBROT;
        if (kd.key == MLX_KEY_2) app->type = FRACT_JULIA;
        if (kd.key == MLX_KEY_3) app->type = FRACT_BURNING_SHIP;
        if (kd.key == MLX_KEY_C) app->palette = (app->palette + 1) % 3;
        if (kd.key == MLX_KEY_R) app_reset(app);
        render_fractal(app);
    }
}

void setup_hooks(t_app *app)
{
    mlx_scroll_hook(app->mlx, on_scroll, app);
    mlx_key_hook(app->mlx, on_key, app);
}
