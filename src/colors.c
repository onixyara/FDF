/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:27:04 by vonischu          #+#    #+#             */
/*   Updated: 2018/10/15 16:16:41 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <limits.h>
#include "../libft/libft.h"

void			read_color(t_vector3 **vec3, char *str, int i)
{
	char		*p;

	if ((p = ft_strchr(str, ',')))
		(*vec3 + i)->color = ft_atoi(p + 1);
	else
		(*vec3 + i)->color = 1;
}

static void		find_depth(t_vector3 **vec3, t_plane *plane)
{
	int			min;
	int			max;
	t_vector3	v;
	t_vector3	*cur;

	min = INT_MAX;
	max = INT_MIN;
	v.y = 0;
	while (v.y < plane->rows)
	{
		v.x = 0;
		while (v.x < plane->colums)
		{
			cur = (*vec3 + (int)v.y * plane->colums + (int)v.x);
			if (cur->z < min)
				min = cur->z;
			if (cur->z > max)
				max = cur->z;
			v.x++;
		}
		v.y++;
	}
	plane->depth_min = min;
	plane->depth_max = max;
}

static void		in_colors(t_vector3 **vec3, t_plane *plane, int step)
{
	int			i;

	i = 0;
	while (i < plane->area)
	{
		if ((*vec3 + i)->color != 1)
			i++;
		if ((*vec3 + i)->z <= (plane->depth_min + step))
			(*vec3 + i)->color = 0x0000008B;
		else if ((*vec3 + i)->z <= (plane->depth_min + (step * 2)))
			(*vec3 + i)->color = 0x00F4A460;
		else if ((*vec3 + i)->z <= (plane->depth_min + (step * 3)))
			(*vec3 + i)->color = 0x00006400;
		else
			(*vec3 + i)->color = 0x00F8F8FF;
		i++;
	}
}

void			fill_colors(t_vector3 **vec3, t_plane *plane)
{
	int			range;
	int			step;
	int			i;

	i = 0;
	find_depth(vec3, plane);
	range = abs(plane->depth_max - plane->depth_min);
	if (range < 4)
	{
		while (i < plane->area)
		{
			if ((*vec3 + i)->color == 1)
				(*vec3 + i)->color = 0x00006400;
			i++;
		}
	}
	else
	{
		step = (range / 4);
		in_colors(vec3, plane, step);
	}
}
