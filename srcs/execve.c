/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 09:17:06 by epfennig          #+#    #+#             */
/*   Updated: 2021/08/09 14:01:08 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_path_correct(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
		return (1);
	return (0);
}

void	exec_path_norme(char *path, char **cmd, char **env)
{
	if (g_data.is_dlredir >= 0)
	{
		dup2(g_data.fd[0], STDIN_FILENO);
		g_data.is_fork = 0;
	}
	if (g_data.is_dlredir >= 0 && g_data.is_redir >= 0)
	{
		dup2(g_data.fd1, STDOUT_FILENO);
		g_data.is_fork = 1;
	}
	if ((execve(path, cmd, env)) == -1)
		exit(1);
}

void	non_builtin_exec(char **cmd, char *path, char **env)
{
	int	ret;
	int	status;

	if (!(check_if_path_correct(path)))
	{
		g_data.exec = 127;
		return (ft_error("bash: ", cmd[0], ": command not found\n"));
	}
	g_data.exec = 0;
	g_data.is_fork = 1;
	echo_control_seq(1);
	ret = fork();
	if (ret == 0)
		exec_path_norme(path, cmd, env);
	else if (ret == -1)
	{
		ft_error("Error: ", strerror(errno), "\n");
		exit(1);
	}
	else
	{
		waitpid(ret, &status, 0);
		g_data.exec = WEXITSTATUS(status);
		g_data.is_fork = 0;
	}
}

void	build_path(char **path, char **splitcmd, char **env)
{
	int			i;
	struct stat	sb;

	i = -1;
	while (path[++i])
	{
		path[i] = ft_realloc(path[i], ft_strlen(path[i]) + 2);
		ft_strlcat(path[i], "/", ft_strlen(path[i]) + 2);
		path[i] = ft_realloc(path[i], sizeof(char) * \
			(ft_strlen(path[i]) + ft_strlen(splitcmd[0]) + 1));
		ft_strlcat(path[i], splitcmd[0], ft_strlen(path[i]) \
			+ ft_strlen(splitcmd[0]) + 1);
		if (stat(path[i], &sb) == 0)
		{
			non_builtin_exec(g_data.exec_tab, path[i], env);
			g_data.success = 1;
			break ;
		}
	}
}

void	boucle_executable(char *cmd, char **env, int j)
{
	char		**path;
	char		*varenv;
	char		**splitcmd;

	g_data.success = 0;
	varenv = ft_getenv("PATH");
	if (!varenv)
	{
		g_data.exec = 127;
		return (ft_error("bash: ", cmd, ": No such file or directory\n"));
	}
	path = ft_split(varenv, ':');
	free(varenv);
	if (g_data.tkcmd[j]->type != TK_STRING)
		splitcmd = ft_split(cmd, ' ');
	else
		splitcmd = ft_split(cmd, '\0');
	build_path(path, splitcmd, env);
	if (!g_data.success)
	{
		g_data.exec = 127;
		ft_error("bash: ", cmd, ": command not found\n");
	}
	free_tab(path);
	free_tab(splitcmd);
}
