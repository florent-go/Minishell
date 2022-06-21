/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:28:20 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/28 10:15:33 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_control_seq(int c)
{
	struct termios	conf;

	ioctl(ttyslot(), TIOCGETA, &conf);
	if (c == 1)
		conf.c_lflag |= ECHOCTL;
	else if (c == 0)
		conf.c_lflag &= ~(ECHOCTL);
	ioctl(ttyslot(), TIOCSETA, &conf);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_data.is_fork == 0 && g_data.is_dlredir < 0)
		{
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
		else if (g_data.is_fork == 1)
		{
			printf("\n");
			rl_on_new_line();
		}
		else if (g_data.is_dlredir >= 0)
		{
			g_data.ctrlc = 1;
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		if (g_data.is_fork == 1)
		{
			printf("Quit: 3\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
		}
	}
}
