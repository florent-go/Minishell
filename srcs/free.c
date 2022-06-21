/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:16:14 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/28 15:38:29 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tabfree)
{
	int	i;

	i = -1;
	while (tabfree[++i])
		free(tabfree[i]);
	free(tabfree);
}

void	free_tkcmd(void)
{
	int	i;

	i = 0;
	if (g_data.tkcmd)
	{
		while (g_data.tkcmd[i]->av)
		{
			if (g_data.tkcmd[i]->av)
				free(g_data.tkcmd[i]->av);
			if (g_data.tkcmd[i])
				free(g_data.tkcmd[i]);
			i++;
		}
		if (g_data.tkcmd[i])
			free(g_data.tkcmd[i]);
		if (g_data.tkcmd)
			free(g_data.tkcmd);
	}
}

void	free_all(void)
{
	free_tkcmd();
	free_tab(g_data.exec_tab);
	if (g_data.lexer)
		free(g_data.lexer);
}
