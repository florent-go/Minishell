/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tabcmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:09:32 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/21 18:26:39 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_exectab2(int i, int j)
{
	g_data.exec_tab = (char **)malloc(sizeof(char *) * (g_data.nbtabexec + 1));
	while (i < g_data.nbtabexec)
	{
		g_data.exec_tab[i] = ft_strdup(g_data.tkcmd[j]->av);
		j++;
		i++;
	}
	g_data.exec_tab[i] = NULL;
}

void	is_arrstart(void)
{
	if (g_data.tkcmd[0]->av && (g_data.tkcmd[0]->type == TK_PIPE
			|| g_data.tkcmd[0]->type == TK_ARR_R
			|| g_data.tkcmd[0]->type == TK_D_ARR_R
			|| g_data.tkcmd[0]->type == TK_ARR_L
			|| g_data.tkcmd[0]->type == TK_D_ARR_L))
	{
		g_data.arrstart = 1;
	}
}

void	init_exectab(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	is_arrstart();
	if (g_data.arrstart == 1)
	{
		j = 2;
		i += 2;
	}
	g_data.nbtabexec = 0;
	while (g_data.tkcmd[i]->av && (g_data.tkcmd[i]->type != TK_PIPE
			&& g_data.tkcmd[i]->type != TK_ARR_R
			&& g_data.tkcmd[i]->type != TK_D_ARR_R
			&& g_data.tkcmd[i]->type != TK_ARR_L
			&& g_data.tkcmd[i]->type != TK_D_ARR_L))
	{
		g_data.nbtabexec++;
		i++;
	}
	i = 0;
	init_exectab2(i, j);
}
