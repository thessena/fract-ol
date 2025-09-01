#include "../inc/fractol.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int str_eq(const char* a, const char* b) { return strcmp(a,b) == 0; }

void print_usage(const char *prog)
{
    fprintf(stderr,
        "Usage:\n"
        "  %s mandelbrot\n"
        "  %s julia <cx> <cy>\n"
        "  %s burning\n"
        "Options:\n"
        "  --iter N       Initial max iterations (default 100)\n"
        "  --palette P    classic|fire|ocean (default classic)\n",
        prog, prog, prog);
}

static t_palette parse_palette(const char* s)
{
    if (str_eq(s, "classic")) return PAL_CLASSIC;
    if (str_eq(s, "fire")) return PAL_FIRE;
    if (str_eq(s, "ocean")) return PAL_OCEAN;
    return PAL_CLASSIC;
}

bool parse_args(t_app *app, int argc, char **argv)
{
    memset(app, 0, sizeof(*app));
    app->zoom = 1.0;
    app->palette = PAL_CLASSIC;
    if (argc < 2)
    {
        print_usage(argv[0]);
        return false;
    }
    if (str_eq(argv[1], "mandelbrot"))
        app->type = FRACT_MANDELBROT;
    else if (str_eq(argv[1], "julia"))
    {
        app->type = FRACT_JULIA;
        if (argc < 4)
        {
            fprintf(stderr, "Error: julia requires <cx> <cy> parameters\n");
            print_usage(argv[0]);
            return false;
        }
        app->julia_cx = strtod(argv[2], NULL);
        app->julia_cy = strtod(argv[3], NULL);
    }
    else if (str_eq(argv[1], "burning"))
        app->type = FRACT_BURNING_SHIP;
    else
    {
        fprintf(stderr, "Error: unknown fractal '%s'\n", argv[1]);
        print_usage(argv[0]);
        return false;
    }
    for (int i = 2; i < argc; ++i)
    {
        if (str_eq(argv[i], "--iter") && i + 1 < argc)
        {
            app->max_iter = (int)strtol(argv[++i], NULL, 10);
            if (app->max_iter < 10) app->max_iter = 10;
        }
        else if (str_eq(argv[i], "--palette") && i + 1 < argc)
        {
            app->palette = parse_palette(argv[++i]);
        }
    }
    return true;
}

