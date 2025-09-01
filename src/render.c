#include "../inc/fractol.h"
#include <math.h>

static int mandelbrot(double cr, double ci, int max_iter)
{
    double zr = 0.0, zi = 0.0;
    int i = 0;
    while (i < max_iter)
    {
        double zr2 = zr*zr - zi*zi + cr;
        zi = 2.0*zr*zi + ci;
        zr = zr2;
        if (zr*zr + zi*zi > 4.0)
            break;
        ++i;
    }
    return i;
}

static int julia(double zr, double zi, double cr, double ci, int max_iter)
{
    int i = 0;
    while (i < max_iter)
    {
        double zr2 = zr*zr - zi*zi + cr;
        zi = 2.0*zr*zi + ci;
        zr = zr2;
        if (zr*zr + zi*zi > 4.0)
            break;
        ++i;
    }
    return i;
}

static int burning_ship(double cr, double ci, int max_iter)
{
    double zr = 0.0, zi = 0.0;
    int i = 0;
    while (i < max_iter)
    {
        double azr = fabs(zr), azi = fabs(zi);
        double zr2 = azr*azr - azi*azi + cr;
        zi = 2.0*azr*azi + ci;
        zr = zr2;
        if (zr*zr + zi*zi > 4.0)
            break;
        ++i;
    }
    return i;
}

static void pixel_to_complex(t_app *app, int x, int y, double *out_r, double *out_i)
{
    double scale = 3.0 / (double)app->height; // Fit height to 3.0 units by default
    scale /= app->zoom;
    double r = app->center_x + (x - app->width * 0.5) * scale;
    double i = app->center_y + (y - app->height * 0.5) * scale;
    *out_r = r;
    *out_i = i;
}

void render_fractal(t_app *app)
{
    for (int y = 0; y < app->height; ++y)
    {
        for (int x = 0; x < app->width; ++x)
        {
            double cr, ci;
            pixel_to_complex(app, x, y, &cr, &ci);
            int iter = 0;
            if (app->type == FRACT_MANDELBROT)
                iter = mandelbrot(cr, ci, app->max_iter);
            else if (app->type == FRACT_JULIA)
                iter = julia(cr, ci, app->julia_cx, app->julia_cy, app->max_iter);
            else
                iter = burning_ship(cr, ci, app->max_iter);

            if (iter >= app->max_iter)
                mlx_put_pixel(app->img, x, y, pack_rgba(0,0,0,255));
            else
            {
                double t = (double)iter / (double)app->max_iter;
                uint32_t c = palette_color(app, t);
                mlx_put_pixel(app->img, x, y, c);
            }
        }
    }
}
