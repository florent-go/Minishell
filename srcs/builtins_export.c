/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:04:10 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 13:45:05 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_string(t_env *new)
{
	g_data.i++;
	while (g_data.cmd[g_data.i] != '"')
	{
		if (g_data.cmd[g_data.i] == ' ')
			return (1);
		g_data.i++;
	}
	g_data.i += 2;
	if (g_data.name)
		free(g_data.name);
	g_data.name = ft_strdup(g_data.tkcmd[g_data.j]->av);
	norminette_friendly(new);
	return (0);
}

int	export_simpleq(t_env *new)
{
	g_data.i++;
	while (g_data.cmd[g_data.i] != '\'')
	{
		if (g_data.cmd[g_data.i] != ' ')
			return (1);
		g_data.i++;
	}
	g_data.i += 2;
	if (g_data.name)
		free(g_data.name);
	g_data.name = ft_strdup(g_data.tkcmd[g_data.j]->av);
	norminette_friendly(new);
	return (0);
}

void	export_id(t_env *new)
{
	while (g_data.cmd[g_data.i] != '\0'
		&& g_data.cmd[g_data.i] != ' '
		&& g_data.cmd[g_data.i] != '=')
		g_data.i++;
	g_data.i++;
	if (g_data.name)
		free(g_data.name);
	g_data.name = ft_strdup(g_data.tkcmd[g_data.j]->av);
	norminette_friendly(new);
}

void	norme_export(int ok)
{
	if (ok == 1)
	{
		if (export_string(g_data.new) == 1)
		{
			g_data.exec = 1;
			ft_putstr_fd("bash: export: not a valid identifier\n",
				STDERR_FILENO);
		}
	}
	else if (ok == 0)
	{
		if (export_simpleq(g_data.new) == 1)
		{
			g_data.exec = 1;
			ft_putstr_fd("bash: export: not a valid identifier\n",
				STDERR_FILENO);
		}
	}
}

void	export_handle(t_data *data)
{
	init_ij();
	while (++g_data.j < g_data.ac && (g_data.tkcmd[g_data.j]->type != 8
			&& g_data.tkcmd[g_data.j]->type != 9))
	{
		if (data->tkcmd[g_data.j]->type == 0)
			export_id(g_data.new);
		else if (data->tkcmd[g_data.j]->type == 2)
			norme_export(1);
		else if (data->tkcmd[g_data.j]->type == 11)
			norme_export(0);
		else
		{
			g_data.exec = 1;
			ft_putstr_fd("bash: export: not a valid identifier\n",
				STDERR_FILENO);
		}
		while (g_data.cmd[g_data.i] != '=')
		{
			g_data.i++;
			if (g_data.cmd[g_data.i] == '\0')
				return ;
		}
	}
	if (g_data.name)
		free(g_data.name);
}
