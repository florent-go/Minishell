/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_id.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edracoon <edracoon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 15:21:14 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/27 11:22:25 by edracoon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_alpha_string(t_lexer *lexer)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = 0;
	while (ft_isalpha(lexer->c) || ft_isdigit(lexer->c))
	{
		str = ft_realloc(str, ft_strlen(str) + 2);
		ft_strlcat(str, &lexer->c, ft_strlen(str) + 2);
		lexer_advance(lexer);
	}
	return (str);
}

char	*lexer_dollar_id(t_lexer *lexer, char *values, char *s)
{
	char	*alphastr;

	lexer_advance(lexer);
	if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c))
	{
		alphastr = get_alpha_string(lexer);
		s = ft_getenv(alphastr);
		free(alphastr);
		values = ft_realloc(values, (ft_strlen(values) + ft_strlen(s) + 1));
		ft_strlcat(values, s, ft_strlen(values) + ft_strlen(s) + 1);
		free(s);
	}
	else if (lexer->c == '?')
	{
		values = ft_itoa(g_data.exec);
		lexer_advance(lexer);
	}
	return (values);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*values;
	char	*s;

	values = malloc(1);
	values[0] = '\0';
	while (ft_isprint(lexer->c))
	{
		if (ft_isprint_token(lexer->c))
		{
			lexer_back(lexer);
			break ;
		}
		if (lexer->c == '$')
			return (init_token(TK_ID, lexer_dollar_id(lexer, values, s)));
		s = lexer_get_current_char_as_string(lexer, 0);
		values = ft_realloc(values, (ft_strlen(values) + ft_strlen(s) + 1));
		ft_strlcat(values, s, ft_strlen(values) + ft_strlen(s) + 1);
		free(s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TK_ID, values));
}
