/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thessena <thessena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:31:45 by thessena          #+#    #+#             */
/*   Updated: 2025/09/05 14:44:10 by thessena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdint.h>
# include <stdbool.h>
# include <stdarg.h>
# include <unistd.h>
# include "../mlx42/include/MLX42/MLX42.h"

typedef struct s_cpx
{
	double	re;
	double	im;
}	t_cpx;

typedef enum e_fractal
{
	FRACT_MANDELBROT = 0,
	FRACT_JULIA = 1,
	FRACT_BURNING_SHIP = 2
}	t_fractal;

typedef enum e_palette
{
	PAL_CLASSIC = 0,
	PAL_FIRE = 1,
	PAL_OCEAN = 2
}	t_palette;

typedef struct s_app
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
	double		center_x;
	double		center_y;
	double		zoom;
	int			max_iter;
	t_fractal	type;
	double		julia_cx;
	double		julia_cy;
	bool		julia_lock;
	t_palette	palette;
}	t_app;

// app.c
bool		app_init(t_app *app, int w, int h, const char *title);
void		app_destroy(t_app *app);
void		app_reset(t_app *app);

// args.c
bool		parse_args(t_app *app, int argc, char **argv);
void		print_usage(const char *prog);

// render.c
void		render_fractal(t_app *app);

// input.c
void		setup_hooks(t_app *app);

// color utils.c / palette.c
uint32_t	pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint32_t	lerp_color(uint32_t c1, uint32_t c2, double t);
uint32_t	palette_color(t_app *app, double t);

// ft_printf.c
int			ft_printf(const char *fmt, ...);

// ft_printf_conv.c
int			ft_handle_conv(char c, va_list *ap);

// ft_printf_write.c
int			ft_put_char(char c);
int			ft_put_str(const char *s);

// ft_printf_num.c
int			ft_put_signed(long n);
int			ft_put_unsigned_base(unsigned long n, unsigned int base, int upper);
int			ft_put_ptr(uintptr_t p);

#endif
