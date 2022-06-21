/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 14:51:09 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 11:44:54 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_string2(int j, int i)
{
	write(1, g_data.tkcmd[j]->av,
		ft_strlen(g_data.tkcmd[j]->av));
	while (g_data.cmd[i])
	{
		i++;
		if (g_data.cmd[i] == '\'')
			break ;
	}
	if (g_data.cmd[i] != '\0')
		i++;
	if (g_data.cmd[i] == ' ')
	{
		write(1, " ", 1);
		i++;
		while (g_data.cmd[i] == ' ')
			i++;
	}
	return (i);
}

int	parse_string(int j, int i)
{
	write(1, g_data.tkcmd[j]->av,
		ft_strlen(g_data.tkcmd[j]->av));
	while (g_data.cmd[i])
	{
		i++;
		if (g_data.cmd[i] == '"')
			break ;
	}
	if (g_data.cmd[i] != '\0')
		i++;
	if (g_data.cmd[i] == ' ')
	{
		write(1, " ", 1);
		i++;
		while (g_data.cmd[i] == ' ')
			i++;
	}
	return (i);
}

void	affiche_echo(int j, int i)
{
	while (++j < g_data.ac && (g_data.tkcmd[j]->type != 8
			&& g_data.tkcmd[j]->type != 9))
	{
		if (g_data.tkcmd[j]->type == TK_STRING)
			i = parse_string(j, i);
		else if (g_data.tkcmd[j]->type == TK_SIMPLQ)
			i = parse_string2(j, i);
		else
		{
			write(1, g_data.tkcmd[j]->av, ft_strlen(g_data.tkcmd[j]->av));
			while (g_data.cmd[i])
			{
				if (g_data.cmd[i] == ' ' || g_data.cmd[i] == '"'
					|| g_data.cmd[i++] == '\'')
					break ;
			}
			if (g_data.cmd[i] == ' ')
			{
				write(1, " ", 1);
				i++;
				while (g_data.cmd[i] == ' ')
					i++;
			}
		}
	}
}

void	echo_handle(int j)
{
	int	i;
	int	flag;

	i = 5;
	flag = 0;
	if (g_data.tkcmd[j]->av == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (g_data.is_pipe > 0)
		return ;
	flag = check_arg(i, j, flag);
	if (flag != 1)
		write(1, "\n", 1);
}
