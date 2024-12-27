/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louisalah <louisalah@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/27 14:20:34 by louisalah        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	color = 0;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (color);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	color = (*(unsigned int *)dst);
	return (color);
}

static void	draw_square(t_vars *vars, int x_start, int y_start, int color)
{
	int	x;
	int	y;

	y = y_start;
	while (y + 1 < y_start + vars->size)
	{
		x = x_start;
		while (x + 1 < x_start + vars->size)
		{
			my_put_pixel(vars, x, y, color);
			x++;
		}
		y++;
	}
}

int check_dist(t_vars *vars, float angle)
{
    int dist = 0;
    int size = vars->size;
    float x_step = cos((angle * M_PI) / 180);
    float y_step = -sin((angle * M_PI) / 180);
    float next_x, next_y;
    int current_cell_x = (int)(vars->r_x / size);
    int current_cell_y = (int)(vars->r_y / size);

    while (vars->map[current_cell_y][current_cell_x] == '0')
    {
        next_x = vars->r_x + x_step;
        next_y = vars->r_y + y_step;
        int new_cell_x = (int)(next_x / size);
        int new_cell_y = (int)(next_y / size);

        if (new_cell_x != current_cell_x || new_cell_y != current_cell_y)
        {
            if (new_cell_y != current_cell_y && new_cell_x != current_cell_x)
            {
                if (ft_abs(new_cell_y - current_cell_y) > ft_abs(new_cell_x - current_cell_x))
                    vars->hit_type = 'H';
                else
                    vars->hit_type = 'V';
            }
            if (new_cell_y != current_cell_y)
                vars->hit_type = 'H';
            else if (new_cell_x != current_cell_x)
                vars->hit_type = 'V';
            current_cell_x = new_cell_x;
            current_cell_y = new_cell_y;
        }
        vars->r_x = next_x;
        vars->r_y = next_y;
        dist++;
    }
    return dist;
}


void	draw_3d_line(t_vars *vars, float x, float dist, float angle, t_img *txt_img)
{
	int		y;
	int		color;
	float	t_x;
	float	t_y;
	float	max;
	float	y_step;

	dist *= cos(((angle - vars->angle) * M_PI) / 180)*1.5;
	dist = (vars->size / dist) * ((1000 / 2) / tan((30 * M_PI) / 180));
	t_y = 0;
	y_step = (float)txt_img->height / dist;
	if (vars->hit_type == 'V')
		t_x = ((float)((int)vars->r_y % vars->size)
				/ (vars->size)) * txt_img->width;
	else
		t_x = ((float)((int)vars->r_x % vars->size)
				/ (vars->size)) * txt_img->width;
	y = (1000 / 2) - (dist / 2);
	if (y < 0)
		y = 0;
	max = (1000 / 2) + (dist / 2);
	while (y < max && y < 1000)
	{
		color = my_mlx_pixel_get(txt_img, t_x, t_y);
		my_put_pixel(vars, x, y, color);
		t_y += y_step;
		y++;
	}
}

static void	draw_cursor(t_vars *vars, int color)
{
	float	j;
	float	fov;
	float	angle;
	int		n;
	int		k;
	t_img	*txt_img;

	j = -30;
	k = 1000;
	fov = (60.0 / 1000);
	angle = vars->angle;
	vars->angle = adjust_float_angle(vars->angle);
	while (j <= 30)
	{
		n = check_dist(vars, angle+j);
		vars->ray_angle = adjust_float_angle(angle + j);
		if (vars->hit_type == 'V')
		{
			if (vars->ray_angle >= 90 && vars->ray_angle <= 270)
				txt_img = vars->west;
			else
				txt_img = vars->east;
		}
		else
		{
			if (vars->ray_angle >= 0 && vars->ray_angle <= 180)
				txt_img = vars->north;
			else
				txt_img = vars->south;
		}
		draw_3d_line(vars, k--, n,angle+j, txt_img);
		vars->r_x = vars->player_x + (vars->size / 6);
		vars->r_y = vars->player_y + (vars->size / 6);
		j += fov;
	}
}

int rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static void	draw_splited_screen(t_vars *vars)
{
	int	i;
	int	j;
	int c;
	int f;

	i = -1;
	c = rgb_to_hex(vars->ceiling_colors[0], vars->ceiling_colors[1], vars->ceiling_colors[2]);
	f = rgb_to_hex(vars->floor_color[0], vars->floor_color[1], vars->floor_color[2]);
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1000)
		{
			if (i < 500)
				my_put_pixel(vars, j, i, c);
			else
				my_put_pixel(vars, j, i, f);
		}
	}
}

void	render(t_vars *vars)
{
	ft_memset(vars->addr, 0, vars->line_length * 1000);
	draw_splited_screen(vars);
	draw_cursor(vars, 16711680);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
}

int	draw(t_vars *vars)
{
	ft_handle_keys(vars);
	return (0);
}
