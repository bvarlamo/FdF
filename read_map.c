/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:51:02 by bvarlamo          #+#    #+#             */
/*   Updated: 2021/12/14 09:04:50 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "fdf.h"
#include "minilibx_macos/mlx.h"

static int	wcount(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] == c || s[i] == '\n') && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while ((s[i] != c || s[i] == '\n') && s[i])
				i++;
			count++;
		}
	}
	return (count);
}

static int	row(char *argv, char **line)
{
	int		fd;
	int		rows;
	char	*tmp;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit (write(1, "Error: Cannot open file\n", 24));
	*line = get_next_line(fd);
	tmp = get_next_line(fd);
	rows = 1;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = get_next_line(fd);
		rows++;
	}
	free(tmp);
	close(fd);
	return (rows);
}

static void	spliting(t_values *vars, int fd)
{
	char	**tmp;
	int		i;
	char	*line;
	int		j;

	line = get_next_line(fd);
	i = 0;
	while (line)
	{	
		tmp = ft_split(line, ' ');
		j = 0;
		while (tmp[j])
		{
			vars->map[i][j] = ft_atoi(tmp[j]);
			vars->c_map[i][j] = 0;
			if (ft_strchr(tmp[j], ','))
				vars->c_map[i][j] = ft_hextoi((ft_strchr(tmp[j], ',') + 3));
			free(tmp[j++]);
		}
		free(tmp);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

void	allocation(char *argv, t_values *vars)
{
	char	*line;
	int		i;
	int		fd;

	vars->rows = row(argv, &line);
	vars->columns = wcount(line, ' ');
	vars->map = (int **) malloc(sizeof (int *) * (vars->rows + 1));
	vars->c_map = (int **) malloc(sizeof (int *) * (vars->rows + 1));
	i = 0;
	while (i <= vars->rows)
	{
		vars->map[i] = (int *)malloc(sizeof(int *) * (vars->columns));
		vars->c_map[i] = (int *)malloc(sizeof(int *) * (vars->columns));
		i++;
	}
	vars->map[i - 1] = NULL;
	vars->c_map[i - 1] = NULL;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit (write(1, "Error: Cannot open file\n", 24));
	spliting(vars, fd);
}
