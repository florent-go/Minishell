/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 09:58:24 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/28 09:40:04 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_friendly(t_token *token)
{
	if (token->value && ft_strncmp(token->value, "", 2))
		free(token->value);
	if (token)
		free(token);
}

void	tokeniser_loop_two(t_token *token, t_lexer *lexer, int i)
{
	token = lexer_get_next_token(lexer);
	while (token != 0)
	{
		g_data.tkcmd[i] = (t_cmd *)malloc(sizeof(t_cmd));
		if (!(g_data.tkcmd[i]))
			exit(0);
		g_data.tkcmd[i]->av = ft_strdup(token->value);
		g_data.tkcmd[i]->type = token->e_type;
		i++;
		free_token_friendly(token);
		token = lexer_get_next_token(lexer);
	}
	g_data.ac = i;
	g_data.tkcmd[i] = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(g_data.tkcmd[i]))
		exit(0);
	g_data.tkcmd[i]->av = NULL;
	g_data.tkcmd[i]->type = -1;
}

void	tokeniser_loop(void)
{
	int	i;

	i = 0;
	g_data.dotoken = 0;
	g_data.token = lexer_get_next_token(g_data.lexer);
	while (g_data.token != 0)
	{
		i++;
		if (!g_data.token)
			break ;
		free_token_friendly(g_data.token);
		g_data.token = lexer_get_next_token(g_data.lexer);
	}
	if (g_data.lexer)
	{
		free(g_data.lexer);
		g_data.lexer = NULL;
	}
	g_data.lexer = init_lexer(g_data.cmd);
	g_data.tkcmd = (t_cmd **)malloc(sizeof(t_cmd) * (i + 1));
	if (!g_data.tkcmd)
		exit(0);
	g_data.tkcmd[i] = NULL;
	g_data.dotoken = 1;
	tokeniser_loop_two(g_data.token, g_data.lexer, 0);
}
