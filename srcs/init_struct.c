/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 14:14:19 by fgomez            #+#    #+#             */
/*   Updated: 2021/06/28 15:29:58 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_data(void)
{
	g_data.cmd = NULL;
	g_data.ctrlc = 0;
	g_data.ac = 0;
	g_data.on = 0;
	g_data.is_dlredir = -1;
	g_data.is_redir = -1;
	g_data.dotoken = 0;
	g_data.is_pipe = -1;
	g_data.quoterror = 0;
	g_data.is_fork = 0;
	g_data.arrstart = 0;
	g_data.nbtabexec = 0;
	g_data.lexer = NULL;
	g_data.token = NULL;
	return (1);
}
