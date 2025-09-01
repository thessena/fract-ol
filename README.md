# fract-ol (MLX42)

A fractal explorer supporting Mandelbrot, Julia, and Burning Ship using MLX42.

## Build

- Requires MLX42 in `mlx42` (clone https://github.com/codam-coding-college/MLX42 into `mlx42`).
- Build MLX42 with CMake (the Makefile will do this automatically on first build).

```
make
```

The Makefile detects macOS vs Linux and links accordingly.

## Run

```
./fract-ol mandelbrot [--iter N] [--palette classic|fire|ocean]
./fract-ol julia <cx> <cy> [--iter N] [--palette ...]
./fract-ol burning [--iter N] [--palette ...]
```

Examples:

```
./fract-ol mandelbrot --iter 200 --palette fire
./fract-ol julia -0.8 0.156 --iter 300 --palette ocean
./fract-ol burning --iter 250
```

## Controls

- Arrows / WASD: Pan
- Mouse wheel: Zoom at cursor
- +/-: Increase/decrease iterations
- 1/2/3: Mandelbrot/Julia/Burning Ship
- C: Cycle color palette
- R: Reset view
- ESC: Quit

## Notes

- For Julia, the constant is provided on the command line (`<cx> <cy>`).
- If colors appear swapped on your platform, adjust `pack_rgba` in `src/color.c`.
