/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asid-ahm <asid-ahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:11:18 by asid-ahm          #+#    #+#             */
/*   Updated: 2024/12/24 23:28:15 by asid-ahm         ###   ########.fr       */
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

// int w_get_pixel(t_vars *vars, int b_x, int b_y)
// {
// 	float	x;
// 	float	y;
// 	float	y_step;
// 	int		color;

// 	y = 0;
// 	color = 0;
// 	y_step = (float)vars->north->height / data->line_height;
// 	if (is_vert)
// 		x = ((float)((int)data->vy % data->map->pixel)
// 				/ (data->map->pixel)) * img->width;
// 	else
// 		x = ((float)((int)data->hx % data->map->pixel)
// 				/ (data->map->pixel)) * img->width;
// 	while (data->start < data->end)
// 	{
// 		color = my_mlx_pixel_get(img, x, y);
// 		my_mlx_pixel_put(data->screen, data->x_screen, data->start++, color);
// 		y += y_step;
// 	}
// }


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


// int check_dist(float x, float y, t_vars *vars, float angle)
// {
// 	int dist = 0;
// 	int size = vars->size;

// 	while (vars->map[(int)(y / size)][(int)(x / size)] == '0')
// 	{
// 		x += cos((angle * M_PI) / 180);
// 		y -= sin((angle * M_PI) / 180);
// 		dist++;
// 	}
// 	return (dist);
// }

int check_dist(t_vars *vars, float angle)
{
    int dist = 0;
    int size = vars->size;
    float x_step = cos((angle * M_PI) / 180);
    float y_step = -sin((angle * M_PI) / 180);
    float next_x, next_y;

    while (vars->map[(int)(vars->r_y / size)][(int)(vars->r_x / size)] == '0')
    {
        next_x = vars->r_x + x_step;
        next_y = vars->r_y + y_step;
		if ((int)(next_y / size) != (int)(vars->r_y / size) && (int)(next_x / size) != (int)(vars->r_x / size))
		{
			if (ft_abs((next_y / size) - (vars->r_y / size)) > ft_abs((next_x / size) - (vars->r_x / size)))
				vars->hit_type = 'H';
			else
				vars->hit_type = 'V';
		}
		else if ((int)(next_y / size) != (int)(vars->r_y / size))
			vars->hit_type = 'H';
		else if ((int)(next_x / size) != (int)(vars->r_x / size))
			vars->hit_type = 'V';		
        vars->r_x = next_x;
        vars->r_y = next_y;
        dist++;
    }

    return dist;
}

void	draw_3d_line(t_vars *vars, float x, float dist, float angle, int color)
{
	int		y;
	float	t_x;
	float	t_y;
	float	y_step;
	float line_h;
	// printf("1 dist: %f\n", dist);
	dist *= cos(((angle - vars->angle) * M_PI) / 180)*1.5;
	// printf("2 dist: %f\n", dist);

	t_y = 0;
	
	line_h = (vars->size / dist) * ((1000 / 2) / tan((30 * M_PI) / 180));
	y_step = (float)vars->north->height / line_h;
	dist = (vars->size / dist) * ((1000 / 2) / tan((30 * M_PI) / 180));
	// printf("3 dist: %f\n", dist);

	if (vars->hit_type == 'V')
		t_x = ((float)((int)vars->r_y % vars->size)
				/ (vars->size)) * vars->north->width;
	else
		t_x = ((float)((int)vars->r_x % vars->size)
				/ (vars->size)) * vars->north->width;
	y = (1000 / 2) - (dist / 2);
	if (y < 0)
		y = 0;
	while (y < ((1000 / 2) + (dist / 2)) && y < 1000)
	{
		color = my_mlx_pixel_get(vars->north, t_x, t_y);
		my_put_pixel(vars, x, y, color);
		t_y += y_step;
		y++;
	}
}

static void	draw_cursor(t_vars *vars, int color)
{
	int		i;
	float	j;
	float	fov;
	float	angle;
	int		x;
	int		y;
	int		n;
	int		k;

	j = -30;
	k = 1000;
	fov = (60.0 / 1000);
	angle = vars->angle;
	while (j <= 30)
	{
		i = 0;
		n = check_dist(vars, angle+j);
		draw_3d_line(vars, k--, n,angle+j, color);
		vars->r_x = vars->player_x + (vars->size / 6);
		vars->r_y = vars->player_y + (vars->size / 6);
		if (vars->hit_type == 'V')
			color = 0x007700;
		else
			color = 0x000077;
		// while (i++ < n)
		// {
		// 	my_put_pixel(vars, vars->r_x, vars->r_y, color);
		// 	vars->r_x += cos(((angle+j) * M_PI) / 180);
		// 	vars->r_y -= sin(((angle+j) * M_PI) / 180);
		// }
		j += fov;
	}
}

void	draw_player(t_vars *vars, int color)
{
	const int	size = vars->size / 3;
	int			x;
	int			y;

	y = 0;
	x = 0;
	draw_cursor(vars, 16711680);
}

int rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	draw_splited_screen(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 1000)
	{
		j = -1;
		while (++j < 1000)
		{
			if (i < 500)
				my_put_pixel(vars, j, i, rgb_to_hex(vars->ceiling_colors[0], vars->ceiling_colors[1], vars->ceiling_colors[2]));
			else
				my_put_pixel(vars, j, i, rgb_to_hex(vars->floor_color[0], vars->floor_color[1], vars->floor_color[2]));
		}
	}
}

int	draw_map2d(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	ft_memset(vars->addr, 0, vars->line_length * 1000);
	draw_splited_screen(vars);
	// while (vars->map[++i])
	// {
	// 	j = -1;
	// 	while (vars->map[i][++j])
	// 	{
	// 		if (vars->map[i][j] == '1')
	// 			draw_square(vars, (j * vars->size), (i * vars->size), 0xD3D3D3);
	// 		else if(vars->map[i][j] == '0' || check_for_player(vars->map[i][j]))
	// 			draw_square(vars, (j * vars->size), (i * vars->size), 0x404040);
	// 	}
	// }
	draw_player(vars, 0x000000CD);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img, 0, 0);
	return (0);
}
