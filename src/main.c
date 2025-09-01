#include "../inc/fractol.h"
#include <stdio.h>

static void on_close(void* param)
{
    t_app* app = (t_app*)param;
    (void)app;
}

int main(int argc, char **argv)
{
    t_app app;

    if (!parse_args(&app, argc, argv))
        return 1;
    if (!app_init(&app, 1000, 800, "fract-ol"))
        return 1;

    render_fractal(&app);
    setup_hooks(&app);
    mlx_close_hook(app.mlx, on_close, &app);
    mlx_loop(app.mlx);

    app_destroy(&app);
    return 0;
}
