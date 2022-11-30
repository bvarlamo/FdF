/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvarlamo <bvarlamo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 22:28:38 by bvarlamo          #+#    #+#             */
/*   Updated: 2021/12/14 12:48:26 by bvarlamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 42
# endif

typedef struct s_values
{
	int			rows;
	int			columns;
	int			**map;
	int			**c_map;
	void		*initi;
	void		*window;
	void		*img;
	char		*add;
	float		x;
	float		y;
	float		x_step;
	float		y_step;
	int			color;
	int			z;
	int			z1;
	int			zoom;
	float		angle;
	int			bits;
	int			line;
	int			end;
	int			shift_x;
	int			shift_y;
}	t_values;

int		drawing(t_values *vars);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_hextoi(char	*hex);
void	allocation(char *argv, t_values *vars);

#endif