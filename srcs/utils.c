/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:15:40 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/25 13:50:26 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_size(void)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = g_data.env;
	while (g_data.env)
	{
		i++;
		g_data.env = g_data.env->next;
	}
	g_data.env = tmp;
	return (i);
}

void	ascii_minishell(void)
{
	int		fd;
	char	*line;

	fd = open("ascii_minishell.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	free(line);
}

char	*ft_realloc(char *src, int size)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	free(src);
	dest[i] = '\0';
	return (dest);
}

int	check_arg(int i, int j, int flag)
{
	while (g_data.cmd[i] == ' ')
		i++;
	while (g_data.cmd[i] == '-')
	{
		i++;
		while (g_data.cmd[i] == 'n')
			i++;
		if (g_data.cmd[i] != ' ' && g_data.cmd[i] != '\0')
			i = 5;
		else
		{
			flag = 1;
			j++;
		}
		while (g_data.cmd[i] == ' ')
			i++;
	}
	affiche_echo(j, i);
	return (flag);
}
