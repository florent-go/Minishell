/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:22:18 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 11:44:26 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putstr_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putstr_fd(s3, STDERR_FILENO);
}

void	execute_cmd(void)
{
	if (g_data.is_redir >= 0 || g_data.is_dlredir >= 0)
	{
		if (g_data.is_dlredir >= 0)
			double_redir_left(g_data.is_dlredir, NULL, g_data.tabenv);
		if (g_data.is_redir >= 0)
			ft_redirection(g_data.tabenv, g_data.is_redir);
	}
	else
		choose_cmd(g_data.tabenv, 0);
}

void	pre_parser_test(void)
{
	g_data.tabenv = listenv_to_tabstr(0);
	if (g_data.tkcmd[0]->type != 0 && g_data.tkcmd[0]->type != 2
		&& g_data.tkcmd[0]->type != 11
		&& g_data.tkcmd[0]->type != 8 && g_data.tkcmd[0]->type != 7
		&& 10 != g_data.tkcmd[0]->type
		&& 9 != g_data.tkcmd[0]->type && g_data.tkcmd[0]->av)
	{
		g_data.exec = 258;
		return (ft_error("bash: syntax error\n", NULL, NULL));
	}
	if (is_dredirleft() == -2 || is_redirect() == -2)
	{
		g_data.exec = 258;
		return (ft_error("bash: syntax error near"
				"unexpected token `newline'\n", NULL, NULL));
	}
	execute_cmd();
	free_tab(g_data.tabenv);
}

void	choose_cmd2(char **env, int j)
{
	if (!(ft_strncmp(g_data.tkcmd[j]->av, "pwd", 4)))
		pwd_print();
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "export", 7)))
		export_handle(&g_data);
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "unset", 6)))
		unset_handle();
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "env", 4)))
		env_print(&g_data);
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "/", 1)))
		non_builtin_exec(g_data.exec_tab, g_data.tkcmd[j]->av, env);
	else
		boucle_executable(g_data.tkcmd[j]->av, env, j);
}

void	choose_cmd(char **env, int j)
{
	if (g_data.tkcmd[0]->type == 7 || g_data.tkcmd[0]->type == 8
		|| g_data.tkcmd[0]->type == 9 || g_data.tkcmd[0]->type == 10)
		j = 2;
	if (!(g_data.tkcmd[j]->av))
		return ;
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "cd", 3)))
	{
		if (g_data.tkcmd[j + 1]->av && g_data.is_redir != j + 1)
			changedircd(g_data.tkcmd[j + 1]->av);
		else
			changedircd(NULL);
	}
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "echo", 5)))
		echo_handle(j);
	else if (!(ft_strncmp(g_data.tkcmd[j]->av, "exit", 5)))
		exit_handle();
	else
		choose_cmd2(env, j);
}
