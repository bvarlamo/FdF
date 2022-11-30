/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:26:51 by bvarlamo          #+#    #+#             */
/*   Updated: 2021/12/14 13:01:05 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fdf.h"
#include "minilibx_macos/mlx.h"

static void	clean_up(t_values *vars)
{
	int	i;

	i = 0;
	mlx_destroy_window(vars->initi, vars->window);
	mlx_destroy_image(vars->initi, vars->img);
	while (i < vars->rows)
	{
		free(vars->map[i]);
		free(vars->c_map[i]);
		i++;
	}
	free(vars->map);
	free(vars->c_map);
	free(vars->initi);
	exit(0);
}

int	keys(int key, t_values *vars)
{
	if (key == 13)
		vars->shift_y -= 10;
	if (key == 1)
		vars->shift_y += 10;
	if (key == 0)
		vars->shift_x -= 10;
	if (key == 2)
		vars->shift_x += 10;
	if (key == 126)
		vars->zoom += 5;
	if (key == 125 && vars->zoom > 10)
		vars->zoom -= 5;
	if (key == 123 && vars->angle < 1.5)
		vars->angle += 0.1;
	if (key == 124 && vars->angle > 0.1)
		vars->angle -= 0.1;
	if (key == 53)
		clean_up(vars);
	mlx_clear_window(vars->initi, vars->window);
	vars->img = mlx_new_image(vars->initi, 1200, 600);
	vars->add = mlx_get_data_addr(vars->img, &vars->bits, &vars->line,
			&vars->end);
	drawing(vars);
	mlx_put_image_to_window(vars->initi, vars->window, vars->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_values	vars;

	if (argc != 2)
		return (write(1, "Error: Correct format: ./fdf map/fdf\n", 35));
	allocation(argv[1], &vars);
	vars.zoom = 30;
	vars.angle = 0.8;
	vars.shift_x = 300;
	vars.shift_y = 150;
	vars.initi = mlx_init();
	vars.window = mlx_new_window(vars.initi, 1200, 600, "FDF");
	vars.img = mlx_new_image(vars.initi, 1200, 600);
	vars.add = mlx_get_data_addr(vars.img, &vars.bits, &vars.line, &vars.end);
	drawing(&vars);
	mlx_put_image_to_window(vars.initi, vars.window, vars.img, 0, 0);
	mlx_key_hook(vars.window, keys, &vars);
	mlx_loop(vars.initi);
	return (0);
}
