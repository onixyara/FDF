/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 09:25:00 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/16 19:16:02 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "../libft/libft.h"

# define PI 3.14159265359
# define IS_ERR3(x, y, z) if (x <= 0 || y == -1 || z == (float)-1) return (-1);
# define IS_ERR1(x) if (x == -1) return (-1);
# define IS_NULL(x) if (x == NULL) return (NULL);

typedef struct		s_cam
{
	float		offsetx;
	float		offsety;
	float		x;
	float		y;
	int			scale;
}					t_cam;

typedef struct	s_vector3
{
	float		z;
	int			x;
	int			y;
	int			color;
}				t_vector3;

typedef struct	s_vector2
{
	float		x;
	float		y;
	int			color;
}				t_vector2;

typedef struct	s_vectors
{
	t_vector3	*vec3;
	t_vector2	*vec2;
	float		angle;
}				t_vectors;

typedef struct	s_plane
{
	int			rows;
	int			colums;
	int			area;
	int			depth_min;
	int			depth_max;
}				t_plane;

typedef struct	s_mouse
{
	char		isdown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}				t_mouse;

typedef struct	s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			stride;
	int			endian;
}				t_image;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_image		image;
	t_plane		*plane;
	t_mouse		*mouse;
	int			size;
	t_vectors	vec;
}				t_mlx;

int				convertor(t_mlx *mlx);
void			update_vec3(t_mlx *mlx, t_vector2 **vec2, t_vector3 **vec3);

t_plane			*is_valid(char **av, t_vector3 **vec3);

float			*write_image(t_mlx *mlx, t_vectors *vec, t_plane *plane);
void			drow_line(t_mlx *mlx, float *arr, int color);
void			put_pixel(t_mlx *mlx, int x, int y, int color);
void			show_keys(t_mlx *mlx);
void			adapt_image(t_vector2 **vec2, int size);
int				ft_strerror(char *reason);
int				check_letter(char **str);
void			read_color(t_vector3 **vec3, char *str, int i);
int				splitdel(char ***split);
t_plane			*parcer(char *file_name, t_vector3 **vec3, t_plane *plane);


void			zoom_handl(t_mlx *mlx, int key);
void			move_handl(t_mlx *mlx, int key);
void			color_handl(t_mlx *mlx, int key);
void			fill_colors(t_vector3 **vec3, t_plane *plane);

void			esc_free(t_mlx *mlx);
void			plane_free(t_mlx *mlx);

#endif
