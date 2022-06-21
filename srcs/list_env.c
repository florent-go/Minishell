/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:23:11 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 14:04:57 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_var(char **env, char *want, int size)
{
	char	**split;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], want, size))
			split = ft_split(env[i], '=');
		i++;
	}
	return (split[1]);
}

void	stock_env(char **ev)
{
	int		i;
	char	**split;
	t_env	*new;

	i = -1;
	g_data.env = NULL;
	while (ev[++i])
	{
		split = ft_split(ev[i], '=');
		if (!split[1])
		{
			split[1] = NULL;
		}
		new = ft_lstnew(split[0], split[1]);
		if (new)
			ft_lstadd_front(&g_data.env, new);
		free_tab(split);
	}
}

char	**listenv_to_tabstr(int i)
{
	t_env	*tmp;

	tmp = g_data.env;
	g_data.env2 = malloc(sizeof(char *) * (get_env_size() + 1));
	if (!g_data.env2)
		ft_exit("Error: Malloc failed\n");
	while (g_data.env)
	{
		g_data.var = ft_strdup(g_data.env->name);
		g_data.temp = g_data.var;
		free(g_data.var);
		g_data.var = ft_strjoin(g_data.var, "=");
		g_data.temp = g_data.var;
		free(g_data.var);
		if (g_data.env->content)
			g_data.var = ft_strjoin(g_data.temp, g_data.env->content);
		else
			g_data.var = ft_strjoin(g_data.temp, " ");
		g_data.env2[i++] = ft_strdup(g_data.var);
		free(g_data.var);
		g_data.env = g_data.env->next;
	}
	g_data.env2[i] = NULL;
	g_data.env = tmp;
	return (g_data.env2);
}

char	*ft_getenv(char *var)
{
	t_env	*tmp;
	char	*contain;

	contain = NULL;
	tmp = g_data.env;
	while (g_data.env)
	{
		if (!ft_strncmp(var, g_data.env->name, ft_strlen(g_data.env->name) + 1))
		{
			if (g_data.env->content)
				contain = ft_strdup(g_data.env->content);
			else
				contain = NULL;
			break ;
		}
		g_data.env = g_data.env->next;
	}
	g_data.env = tmp;
	return (contain);
}

int	ft_getname(char *var)
{
	t_env	*tmp;
	int		good;

	good = 0;
	tmp = g_data.env;
	while (g_data.env)
	{
		if (!ft_strncmp(var, g_data.env->name, ft_strlen(g_data.env->name) + 1))
		{
			good = 1;
			break ;
		}
		g_data.env = g_data.env->next;
	}
	g_data.env = tmp;
	return (good);
}
