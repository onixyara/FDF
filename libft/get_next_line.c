/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 14:52:48 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/15 17:27:11 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char	*concat(char *buf, char *tmp)
{
	size_t	a;
	size_t	b;
	char	*res;

	a = ft_slen(buf);
	b = ft_slen(tmp);
	res = (char *)malloc(sizeof(char *) * (a + b + 1));
	ft_memcpy(res, buf, a);
	ft_memcpy(res + a, tmp, b);
	res[a + b] = '\0';
	ft_memset(tmp, 0, BUFF_SIZE + 1);
	free(buf);
	return (res);
}

static int	check(char **buff, char **tab, char **line)
{
	char	*p;
	int		len;
	char	*str;

	*buff = concat(*buff, *tab);
	len = 0;
	str = *buff;
	while (str[len] != '\n' && str[len])
		len++;
	if (str[len] == '\n')
		str[len] = '\0';
	else
		len = -1;
	if (len >= 0)
	{
		*line = ft_strdup(*buff);
		p = *buff;
		*buff = ft_strdup(*buff + len + 1);
		free(p);
		return (1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	char		*tmp;
	int			res;
	int			i;
	static char *buff[12000];

	tmp = ft_strnew(BUFF_SIZE);
	if (!line || BUFF_SIZE <= 0 || fd < 0 || (i = read(fd, tmp, 0)) < 0)
		return (-1);
	while ((i = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		res = check(&buff[fd], &tmp, line);
		free(tmp);
		if (res == 1)
			return (1);
		tmp = ft_strnew(BUFF_SIZE);
	}
	if ((res = check(&buff[fd], &tmp, line)))
		return (1);
	else if (ft_strlen(buff[fd]) > 0)
	{
		*line = ft_strdup(buff[fd]);
		ft_strdel(&buff[fd]);
		return (1);
	}
	return (res);
}
