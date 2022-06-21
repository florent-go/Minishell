/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:47:41 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 14:04:13 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char *str)
{
	ft_error(str, NULL, NULL);
	exit(1);
}

void	minishell(void)
{
	init_data();
	echo_control_seq(0);
	g_data.cmd = readline("|----( Ed & Flo * minishell )----> ");
	if (g_data.cmd && ft_strlen(g_data.cmd))
		add_history(g_data.cmd);
	if (g_data.cmd == NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(1);
	}
	else if (!(g_data.cmd[0] == 0))
	{
		signal(SIGQUIT, handle_sigquit);
		g_data.lexer = init_lexer(g_data.cmd);
		tokeniser_loop();
		init_exectab();
		if (g_data.quoterror == 0)
			pre_parser_test();
		else
			printf("Error: quote error\n");
		free_all();
	}
	free(g_data.cmd);
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("", 0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)ac;
	g_data.env = NULL;
	g_data.is_env = 0;
	ascii_minishell();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (env[0])
		stock_env(env);
	else
		g_data.is_env = 1;
	while (42)
	{
		minishell();
	}
	return (0);
}
