#include "../inc/fractol.h"
#include <math.h>

uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return ((uint32_t)a << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | (uint32_t)b;
}

static uint32_t lerp_color(uint32_t c1, uint32_t c2, double t)
{
    uint8_t a1 = (c1 >> 24) & 0xFF, r1 = (c1 >> 16) & 0xFF, g1 = (c1 >> 8) & 0xFF, b1 = c1 & 0xFF;
    uint8_t a2 = (c2 >> 24) & 0xFF, r2 = (c2 >> 16) & 0xFF, g2 = (c2 >> 8) & 0xFF, b2 = c2 & 0xFF;
    uint8_t a = (uint8_t)(a1 + (a2 - a1) * t);
    uint8_t r = (uint8_t)(r1 + (r2 - r1) * t);
    uint8_t g = (uint8_t)(g1 + (g2 - g1) * t);
    uint8_t b = (uint8_t)(b1 + (b2 - b1) * t);
    return pack_rgba(r,g,b,a);
}

uint32_t palette_color(t_app *app, double t)
{
    if (t < 0)
        t = 0;
    if (t > 1)
        t = 1;
    if (app->palette == PAL_FIRE)
    {
        uint32_t a = pack_rgba(0, 0, 0, 255);
        uint32_t b = pack_rgba(255, 80, 0, 255);
        uint32_t c = pack_rgba(255, 255, 0, 255);
        if (t < 0.5) return lerp_color(a, b, t * 2.0);
        return lerp_color(b, c, (t - 0.5) * 2.0);
    }
    else if (app->palette == PAL_OCEAN)
    {
        uint32_t a = pack_rgba(0, 7, 100, 255);
        uint32_t b = pack_rgba(32, 107, 203, 255);
        uint32_t c = pack_rgba(237, 255, 255, 255);
        if (t < 0.5) return lerp_color(a, b, t * 2.0);
        return lerp_color(b, c, (t - 0.5) * 2.0);
    }
    else
    {
        uint32_t a = pack_rgba(0, 0, 0, 255);
        uint32_t b = pack_rgba(255, 255, 255, 255);
        return lerp_color(a, b, t);
    }
}
