/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:35:36 by fgomez            #+#    #+#             */
/*   Updated: 2021/08/09 11:21:50 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	boucle_digit(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	exit_handle(void)
{
	int	nb;

	rl_replace_line("", 0);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (g_data.tkcmd[1]->av)
	{
		if (g_data.tkcmd[1]->av && !(g_data.tkcmd[2]->av))
		{
			nb = ft_atoi(g_data.tkcmd[1]->av);
			if (boucle_digit(g_data.tkcmd[1]->av))
				exit(nb);
			else
			{
				ft_putstr_fd("bash: exit: numeric argument required\n", \
					STDERR_FILENO);
				exit(1);
			}
		}
		else if (g_data.tkcmd[2]->av)
			ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
		else
			exit(1);
	}
	else
		exit(1);
}

void	env_print(t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (data->env)
	{
		ft_putstr_fd(data->env->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (data->env->content)
			ft_putstr_fd(data->env->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		data->env = data->env->next;
	}
	data->env = tmp;
}

t_env	*unset_friendly(int i, int j, t_env *tmp)
{
	while (g_data.env)
	{
		if (j == 0 && !ft_strncmp(g_data.tkcmd[i]->av, g_data.env->name,
				ft_strlen(g_data.tkcmd[i]->av) + 1))
		{
			free(g_data.env->name);
			free(g_data.env->content);
			free(g_data.env);
			tmp = g_data.env->next;
			break ;
		}
		else if (!ft_strncmp(g_data.tkcmd[i]->av, g_data.env->next->name,
				ft_strlen(g_data.tkcmd[i]->av) + 1))
		{
			free(g_data.env->next->name);
			free(g_data.env->next->content);
			free(g_data.env->next);
			g_data.env->next = g_data.env->next->next;
			break ;
		}
		j++;
		g_data.env = g_data.env->next;
	}
	return (tmp);
}

void	unset_handle(void)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tmp = g_data.env;
	while (g_data.tkcmd[i]->av)
	{
		if (ft_getname(g_data.tkcmd[i]->av))
			tmp = unset_friendly(i, j, tmp);
		i++;
		g_data.env = tmp;
	}
}
