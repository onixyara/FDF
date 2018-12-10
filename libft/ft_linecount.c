/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linecount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 22:16:00 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/16 18:24:48 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int			ft_1stwordcount(char c)
{
	static int		ret = 0;
	static int		flag = 0;

	if (c == ' ' || c == '\t')
		flag = 0;
	else if (flag == 0 && (c != ' ') && (c != '\t'))
	{
		flag = 1;
		ret++;
	}
	return (ret);
}

int					ft_linecount(char *file, t_doubleint *doubleint)
{
	int				fd;
	char			buf[1];
	int				flag;

	flag = 0;
	fd = 0;
	if (!file || (fd = open(file, O_RDONLY)) == -1 || read(fd, buf, 0) != 0)
	{
		close(fd);
		return (0);
	}
	doubleint->a = 0;
	while (read(fd, buf, 1))
	{
		if (buf[0] == '\n')
		{
			doubleint->a++;
			flag = 1;
		}
		if (flag == 0)
			doubleint->b = ft_1stwordcount(buf[0]);
	}
	doubleint->a = doubleint->a == 0 ? 1 : doubleint->a;
	close(fd);
	return (1);
}
