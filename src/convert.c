/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 18:36:47 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/09 15:54:00 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void			update_vec3(t_mlx *mlx, t_vector2 **vec2, t_vector3 **vec3)
{
	int			i;
	double		cs;
	double		sn;

	i = -1;
	cs = cos(mlx->vec.angle);
	sn = sin(mlx->vec.angle);
	while (++i < mlx->plane->area)
	{
		(*vec3 + i)->z = ((*vec3 + i)->z * cs - (*vec3 + i)->y *
		sn) * cs + (*vec3 + i)->x * sn;
		(*vec3 + i)->x = (*vec2 + i)->x;
		(*vec3 + i)->y = (*vec2 + i)->y;
		(*vec2 + i)->color = (*vec3 + i)->color;
	}
}

static void		convert(t_mlx *mlx, t_vector2 **vec2, t_vector3 **vec3)
{
	int			i;
	double		cs;
	double		sn;

	i = -1;
	cs = cos(mlx->vec.angle);
	sn = sin(mlx->vec.angle);
	while (++i < mlx->plane->area)
	{
		(*vec2 + i)->x = ((*vec3 + i)->x * cs - ((*vec3 + i)->z *
		cs - (*vec3 + i)->y * sn) * sn) * cs + ((*vec3 + i)->y * cs +
		(*vec3 + i)->z * sn) * sn;
		(*vec2 + i)->y = ((*vec3 + i)->y * cs + (*vec3 + i)->z * sn)
		* cs - ((*vec3 + i)->x * cs - ((*vec3 + i)->z * cs - (*vec3 +
		i)->y * sn) * sn) * sn;
	}
	update_vec3(mlx, vec2, vec3);
}

int				convertor(t_mlx *mlx)
{
	float		*p;

	mlx->vec.vec2 = (t_vector2 *)malloc(sizeof(t_vector2) * mlx->plane->area);
	if (mlx->vec.vec2 == NULL)
	{
		free(mlx->vec.vec3);
		plane_free(mlx);
	}
	convert(mlx, &(mlx->vec.vec2), &(mlx->vec.vec3));
	adapt_image(&(mlx->vec.vec2), (mlx->plane)->area);
	if (!(p = write_image(mlx, &mlx->vec, mlx->plane)))
		esc_free(mlx);
	else
		free(p);
	return (1);
}
