/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 18:12:34 by vonischu          #+#    #+#             */
/*   Updated: 2018/10/16 18:45:00 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int			parce_vector(char *line, t_vector3 **vec3,
									t_plane *plane, int y)
{
	char			**arr;
	char			*tmp;
	int				x;

	if (!(arr = ft_strsplit(line, ' ')))
		return (0);
	x = -1;
	if(check_letter(arr) == 0)
	{
		ft_splitdel(&arr);
		return (0);
	}
	while (++x < plane->colums)
	{
		(*vec3 + (y * plane->colums + x))->x = x;
		(*vec3 + (y * plane->colums + x))->y = y;
		(*vec3 + (y * plane->colums + x))->z = ft_atoi(arr[x]);
		if ((tmp = ft_strchr(arr[x], ',')))
			(*vec3 + (y * plane->colums + x))->color = ft_atoi(tmp + 1);
		else
			(*vec3 + (y * plane->colums + x))->color = 1;
	}
	return (1);
}

static int			parce_3dvectors(t_vector3 **vec3, t_plane *plane,
						char **arr)
{
	int				i;

	i = 0;
	while (i < plane->rows)
	{
		if (parce_vector(arr[i], vec3, plane, i) == 0)
			return (0);
		i++;
	}
	fill_colors(vec3, plane);
	return (1);
}

static char			**check_arr(int fd, t_plane *plane)
{
	char			**arr;
	char			*line;
	int				i;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * plane->rows);
	while ((get_next_line(fd, &line) != 0))
	{
		if (plane->colums != words_count(line, ' '))
			return (NULL);
		arr[i] = ft_strdup(line);
		i++;
		free(line);
	}
	return (arr);
}

t_plane				*parcer(char *file_name, t_vector3 **vec3, t_plane *plane)
{
	int				fd;
	char			**arr;
	t_doubleint		*rc;

	rc = (t_doubleint *)malloc(sizeof(t_doubleint));
	ft_linecount(file_name, rc);
	plane->rows = rc->a;
	plane->colums = rc->b;
	fd = open(file_name, O_RDONLY);
	if ((plane->rows <= 0) || fd == -1)
		return (NULL);
	plane->area = plane->colums * plane->rows;
	if ((arr = (check_arr(fd, plane))) == NULL)
		return (NULL);
	*vec3 = (t_vector3 *)malloc(sizeof(t_vector3) * plane->area);
	if ((parce_3dvectors(vec3, plane, arr)) == 0)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (plane);
}
