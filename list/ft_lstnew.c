/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 12:56:11 by epfennig          #+#    #+#             */
/*   Updated: 2021/06/25 12:58:16 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstnew(char *name, char *content)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!(env))
		return (NULL);
	env->name = ft_strdup(name);
	if (content)
	{
		env->content = ft_strdup(content);
	}
	else
		env->content = NULL;
	env->next = NULL;
	return (env);
}
