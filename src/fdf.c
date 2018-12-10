/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 09:13:12 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/16 19:15:18 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../libft/libft.h"
#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void		smlx_init(t_mlx *mlx, t_plane *plane)
{
	int			size;

	size = (plane->area) * 5;
	if (size < 400)
		size = 500;
	if (size > 2000)
		size = 2000;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, size, size, "fdf");
	mlx->image.img = mlx_new_image(mlx->mlx, size, size);
	mlx->image.addr = mlx_get_data_addr(mlx->image.img, &(mlx->image.bpp),
								&(mlx->image.stride), &(mlx->image.endian));
	mlx->size = size;
	mlx->vec.angle = PI / 180 * 15;
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
}

void			adapt_image(t_vector2 **vec2, int size)
{
	int			i;
	float		adapt_x;
	float		adapt_y;

	i = -1;
	adapt_x = 0;
	adapt_y = 0;
	while (++i < size)
	{
		if ((*vec2 + i)->x < 0 && (*vec2 + i)->x < adapt_x)
			adapt_x = (*vec2 + i)->x;
		if ((*vec2 + i)->y < 0 && (*vec2 + i)->y < adapt_y)
			adapt_y = (*vec2 + i)->y;
	}
	i = -1;
	while (++i < size)
	{
		(*vec2 + i)->x -= adapt_x;
		(*vec2 + i)->y -= adapt_y;
	}
}

static int		deal_key(int key, void *param)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)param;
	if (key == 53)
		esc_free(mlx);
	if (key == 34 || key == 31)
		zoom_handl(mlx, key);
	if (key == 126 || key == 125 || key == 123 || key == 124)
		move_handl(mlx, key);
	if (key == 69 || key == 78 || key == 75 || key == 67)
		color_handl(mlx, key);
	return (1);
}

int				ft_strerror(char *reason)
{
	ft_putendl(reason);
	return (1);
}

int				main(int argc, char **argv)
{
	t_mlx		mlx;
	int			fd;

	if (argc < 2)
		return (ft_strerror("error: not enough arguments"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || (!(mlx.plane = is_valid(argv, &(mlx.vec.vec3)))))
		return (ft_strerror("error: invalid file"));
	smlx_init(&mlx, mlx.plane);
	convertor(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.image.img, 0, 0);
	show_keys(&mlx);
	mlx_hook(mlx.win, 2, (1L << 0), &deal_key, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
