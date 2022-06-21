/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epfennig <epfennig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:28:52 by edracoon          #+#    #+#             */
/*   Updated: 2021/06/25 14:43:22 by epfennig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		ft_exit("Error: Malloc failed\n");
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];
	return (lexer);
}

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_exit("Error: Malloc failed\n");
	token->e_type = type;
	token->value = value;
	return (token);
}

t_token	*lexer_leftarrow(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '<')
		return (lexer_advance_with_token(lexer, init_token(TK_D_ARR_L,
					lexer_get_current_char_as_string(lexer, 2))));
	else
	{
		lexer_back(lexer);
		return (lexer_advance_with_token(lexer, init_token(TK_ARR_L,
					lexer_get_current_char_as_string(lexer, 0))));
	}
	return (NULL);
}

t_token	*lexer_rightarrow(t_lexer *lexer)
{
	lexer_advance(lexer);
	if (lexer->c == '>')
		return (lexer_advance_with_token(lexer, init_token(TK_D_ARR_R,
					lexer_get_current_char_as_string(lexer, 1))));
	else
	{
		lexer_back(lexer);
		return (lexer_advance_with_token(lexer, init_token(TK_ARR_R,
					lexer_get_current_char_as_string(lexer, 0))));
	}
	return (NULL);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == '"')
			return (lexer_string(lexer, NULL));
		else if (lexer->c == '\'')
			return (lexer_string_simpleq(lexer, NULL));
		else if (lexer->c == '=')
			return (lexer_advance_with_token(lexer, init_token(TK_EQUALS,
						lexer_get_current_char_as_string(lexer, 0))));
		else if (lexer->c == '|')
			return (lexer_advance_with_token(lexer, init_token(TK_PIPE,
						lexer_get_current_char_as_string(lexer, 0))));
		else if (lexer->c == '<')
			return (lexer_leftarrow(lexer));
		else if (lexer->c == '>')
			return (lexer_rightarrow(lexer));
		else if (lexer->c == ' ')
			lexer_isspace_skip(lexer);
		else if (ft_isprint(lexer->c))
			return (lexer_collect_id(lexer));
		else
			lexer_advance(lexer);
	}
	return ((void *)0);
}
