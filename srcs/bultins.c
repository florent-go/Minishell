/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 13:30:37 by fgomez            #+#    #+#             */
/*   Updated: 2021/08/09 11:53:11 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_print(void)
{
	char	pwd[1000];
	char	*res;

	res = getcwd(pwd, sizeof(pwd));
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	changedircd(char *str)
{
	if (!str)
		chdir(ft_getenv("HOME"));
	else if (chdir(str) == -1)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	g_data.exec = 0;
}

void	norminette_friendly(t_env *new)
{
	if (g_data.tkcmd[g_data.j + 1]->type == 1)
	{
		if (g_data.cmd[g_data.i] == '\0' || g_data.cmd[g_data.i] == ' ')
			norme_friendly2();
		else
		{
			if (g_data.content)
				free(g_data.content);
			g_data.content = ft_strdup(g_data.tkcmd[g_data.j + 2]->av);
			g_data.j += 2;
		}
		if (ft_getname(g_data.name))
			replace_content_env(g_data.name, g_data.content);
		else
		{
			new = ft_lstnew(g_data.name, g_data.content);
			if (new)
				ft_lstadd_front(&g_data.env, new);
		}
	}
}

void	replace_content_env(char *name, char *content)
{
	t_env	*tmp;

	tmp = g_data.env;
	while (g_data.env)
	{
		if (!ft_strncmp(name, g_data.env->name, ft_strlen(name)))
		{
			free(g_data.env->content);
			if (content)
				g_data.env->content = ft_strdup(content);
			else
			{
				g_data.env->content = malloc(1);
				g_data.env->content = NULL;
			}
			break ;
		}
		g_data.env = g_data.env->next;
	}
	g_data.env = tmp;
}
