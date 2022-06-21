/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:43:24 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/28 09:34:46 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect(void)
{
	int	j;

	j = 0;
	g_data.is_redir = -1;
	while (g_data.tkcmd[j]->av != NULL)
	{
		if (g_data.tkcmd[j]->type == TK_ARR_R
			|| g_data.tkcmd[j]->type == TK_D_ARR_R
			|| g_data.tkcmd[j]->type == TK_ARR_L)
		{
			g_data.is_redir = j;
			if (!(g_data.tkcmd[j + 1]->av))
				return (-2);
			if (j == 0)
				g_data.arrstart = 1;
			break ;
		}
		j++;
	}
	return (1);
}

int	is_pipe(void)
{
	int	j;

	j = 0;
	g_data.is_pipe = -1;
	while (g_data.tkcmd[j]->av != NULL)
	{
		if (g_data.tkcmd[j]->type == 5)
		{
			g_data.is_pipe = j;
			break ;
		}
		j++;
	}
	return (1);
}

int	is_dredirleft(void)
{
	int	j;

	j = 0;
	g_data.is_dlredir = -1;
	while (g_data.tkcmd[j]->av != NULL)
	{
		if (ft_strnstr(g_data.tkcmd[j]->av, "<<", 3))
		{
			g_data.is_dlredir = j;
			if (j == 0)
				g_data.arrstart = 1;
			if (!(g_data.tkcmd[j + 1]->av))
				return (-2);
			break ;
		}
		j++;
	}
	return (1);
}
