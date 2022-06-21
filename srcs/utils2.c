/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 07:44:45 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/28 11:20:23 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	norme_friendly2(void)
{
	if (g_data.content)
		free(g_data.content);
	g_data.content = NULL;
	g_data.j += 1;
	if (g_data.cmd[g_data.i] != '\0')
		g_data.i++;
}

void	init_ij(void)
{
	g_data.j = 0;
	g_data.i = 7;
}
