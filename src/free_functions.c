/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:23:40 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/16 18:20:56 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>
#include "../libft/libft.h"

int			splitdel(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = *split;
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*split)[i];
	}
	ft_memdel((void **)split);
	return (0);
}

void		esc_free(t_mlx *mlx)
{
	free(mlx->vec.vec2);
	free(mlx->vec.vec3);
	free(mlx->plane);
	exit(1);
}

void		plane_free(t_mlx *mlx)
{
	free(mlx->plane);
	exit(1);
}
