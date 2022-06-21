/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 11:15:11 by fgomez            #+#    #+#             */
/*   Updated: 2021/08/09 09:29:52 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirection_error(int j)
{
	while (g_data.tkcmd[j + 1]->av != NULL)
		j++;
	if ((g_data.tkcmd[j]->type == TK_ARR_R
			|| g_data.tkcmd[j]->type == TK_D_ARR_R
			|| g_data.tkcmd[j]->type == TK_ARR_L
			|| g_data.tkcmd[j]->type == TK_D_ARR_L))
	{
		g_data.exec = 258;
		ft_error("bash: syntax error near unexpected token `newline'\n",
			NULL, NULL);
		return (1);
	}
	return (0);
}

int	double_redir_left2(char *line)
{
	signal(SIGQUIT, SIG_IGN);
	line = readline("> ");
	if (line == NULL)
	{
		rl_on_new_line();
		rl_redisplay();
		return (1);
	}
	if (g_data.ctrlc == 1)
		return (1);
	if ((!(line[0] == 0)))
	{
		if (ft_strnstr(g_data.tkcmd[g_data.is_dlredir + 1]->av,
				line, ft_strlen(line)))
		{
			free(line);
			return (1);
		}
	}
	g_data.buff = ft_realloc(g_data.buff, \
		ft_strlen(g_data.buff) + ft_strlen(line) + 2);
	ft_strlcat(g_data.buff, line, ft_strlen(line) + ft_strlen(g_data.buff) + 2);
	ft_strlcat(g_data.buff, "\n", 1 + ft_strlen(g_data.buff) + 2);
	free(line);
	return (0);
}

void	double_redir_left(int j, char *line, char **env)
{
	pipe(g_data.fd);
	g_data.buff = malloc(sizeof(char));
	g_data.buff[0] = 0;
	if (redirection_error(j))
		return ;
	while (1)
	{
		if (double_redir_left2(line) == 1)
			break ;
	}
	write(g_data.fd[1], g_data.buff, ft_strlen(g_data.buff));
	close(g_data.fd[1]);
	if (g_data.buff)
		free(g_data.buff);
	if (g_data.is_redir < 0)
		choose_cmd(env, 0);
}

void	ft_redirection2(int j)
{
	if (ft_strnstr(g_data.tkcmd[j]->av, ">", 1)
		|| ft_strnstr(g_data.tkcmd[j]->av, ">>", 2))
	{
		if (!(g_data.tkcmd[j + 1]->av))
		{
			g_data.exec = 258;
			ft_error("bash: syntax error near unexpected token `newline'\n",
				NULL, NULL);
			exit(1);
		}
		else if (ft_strnstr(g_data.tkcmd[j]->av, ">>", 2))
			g_data.fd1 = open(g_data.tkcmd[j + 1]->av,
					O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			g_data.fd1 = open(g_data.tkcmd[j + 1]->av,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
		dup2(g_data.fd1, STDOUT_FILENO);
		close(g_data.fd1);
	}
	else
	{
		g_data.fd2 = open(g_data.tkcmd[j + 1]->av, O_RDONLY);
		dup2(g_data.fd2, STDIN_FILENO);
		close(g_data.fd2);
	}
}

void	ft_redirection(char **env, int j)
{
	int	pid;

	if (redirection_error(j))
		return ;
	g_data.is_fork = 1;
	pid = fork();
	if (pid == 0)
	{
		while (g_data.tkcmd[j]->av != NULL)
		{
			ft_redirection2(j);
			j++;
		}
		choose_cmd(env, 0);
		exit(1);
	}
	else
	{
		wait(&pid);
		if (!WIFEXITED(pid))
			exit(1);
	}
}
