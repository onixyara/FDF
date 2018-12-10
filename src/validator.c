/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:12:59 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/15 20:59:11 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static int		valid_color(char *str, int j)
{
	int			y;

	y = 1;
	if ((str[j] != '0') || (str[j + 1] != 'x'))
		return (0);
	while (++y < 8)
	{
		if ((ft_ishex(str[j + y])) == 0)
		{
			return (0);
		}
	}
	if (str[j + y] != '\0')
		return (0);
	return (1);
}

static int		cc_validator(char **str)
{
	if ((valid_color(str[1], 0) == 0))
	{
		ft_strerror("error: invalid color");
		return (0);
	}
	else
		return (1);
}

int				check_letter(char **str)
{
	int			i;
	int			j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		if (str[i][0] == '-')
			j++;
		while (str[i][++j])
		{
			if ((ft_isnumeric(&str[i][j])) == 0)
			{
				if (words_count(str[i], ',') != 2)
				{
					ft_strerror("error: invalid map");
					return (0);
				}
				else if (!(cc_validator(ft_strsplit(str[i], ','))))
					return (0);
			}
		}
	}
	return (1);
}

t_plane			*is_valid(char **av, t_vector3 **vec3)
{
	t_plane		*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!(plane = parcer(av[1], vec3, plane)))
	{
		free(plane);
		exit(-1);
	}
	return (plane);
}
