/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:27:47 by bvarlamo          #+#    #+#             */
/*   Updated: 2021/12/14 12:49:57 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"
#include "minilibx_macos/mlx.h"

int	who(float x_step, float y_step)
{
	if (x_step < 0)
		x_step = -x_step;
	if (y_step < 0)
		y_step = -x_step;
	if (x_step > y_step)
		return (x_step);
	else
		return (y_step);
}

void	isometric(float *x, float *y, int z, t_values *vars)
{
	*x *= vars->zoom;
	*y *= vars->zoom;
	*x = (*x - *y) * cos(vars->angle);
	*y = (*x + *y) * sin(vars->angle) - z;
	*x += vars->shift_x;
	*y += vars->shift_y;
}

void	color(float x1, float y1, t_values *vars)
{
	vars->z = vars->map[(int)vars->y][(int)vars->x];
	vars->z1 = vars->map[(int)y1][(int)x1];
	vars->color = 0xffffff;
	if (vars->z < 0 || vars->z1 < 0)
		vars->color = 0x00FF00;
	if (vars->z > 0 || vars->z1 > 0)
		vars->color = 0xe80c0c;
	if (vars->c_map[(int)vars->y][(int)vars->x])
		vars->color = vars->c_map[(int)vars->y][(int)vars->x];
}

static void	put_pixels(float x1, float y1, t_values *vars)
{
	float		x;
	float		y;
	int			max;
	char		*pix;

	x = vars->x;
	y = vars->y;
	color(x1, y1, vars);
	isometric(&x, &y, vars->z, vars);
	isometric(&x1, &y1, vars->z1, vars);
	vars->x_step = x1 - x;
	vars->y_step = y1 - y;
	max = who(vars->x_step, vars->y_step);
	vars->x_step /= max;
	vars->y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		if (x >= 0 && x < 1200 && y >= 0 && y < 600)
		{
			pix = vars->add + ((int)y * vars->line) + (int)x * (vars->bits / 8);
			*(unsigned int *)pix = vars->color;
		}
		y += vars->y_step;
		x += vars->x_step;
	}
}

int	drawing(t_values *vars)
{
	vars->y = 0;
	while (vars->y < vars->rows)
	{
		vars->x = 0;
		while (vars->x < vars->columns)
		{
			if (vars->x < (vars->columns - 1))
				put_pixels(vars->x + 1, vars->y, vars);
			if (vars->y < vars->rows - 1)
				put_pixels(vars->x, vars->y + 1, vars);
			vars->x++;
		}
		vars->y++;
	}
	return (0);
}
