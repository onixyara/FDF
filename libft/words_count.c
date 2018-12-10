/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vonischu <vonischu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 12:36:58 by apavlyuc          #+#    #+#             */
/*   Updated: 2018/10/12 16:47:18 by vonischu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			words_count(char const *s, char del)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == del)
			i++;
		if (*(s + i) != '\0')
			count++;
		while (*(s + i) != del && *(s + i) != '\0')
			i++;
	}
	return (count);
}
