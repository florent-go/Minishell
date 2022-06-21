/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:57:38 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/25 16:58:40 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_next_line_tmp(char **line, int l, char c)
{
	char	*tmp;
	int		i;

	tmp = malloc(l);
	if (!tmp)
	{
		free(*line);
		return (-1);
	}
	i = -1;
	while (++i < l - 2)
		tmp[i] = (*line)[i];
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int		l;
	int		r;
	char	c;

	r = 0;
	l = 1;
	*line = malloc(l);
	if (!*line)
		return (-1);
	(*line)[0] = 0;
	r = read(fd, &c, 1);
	while (r && l++ && c != '\n')
	{
		if (get_next_line_tmp(line, l, c) < 0)
			return (-1);
		r = read(fd, &c, 1);
	}
	return (r);
}
