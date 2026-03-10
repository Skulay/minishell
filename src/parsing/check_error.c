/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:34:36 by alehamad          #+#    #+#             */
/*   Updated: 2026/03/10 18:39:57 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_error(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type == ERROR)
			return (false);
		curr = curr->next;
	}
	return (true);
}

bool	check_tok(t_token *token)
{
	t_token	*curr;

	if (!token || token->type != WORD)
	{
		printf("minishell: syntax error near unexpected token\n");
		return (false);
	}
	curr = token;
	while (curr->next)
	{
		if (curr->type != WORD && curr->next->type != WORD)
		{
			printf("minishell: syntax error near unexpected token\n");
			return (false);
		}
		curr = curr->next;
	}
	if (curr->type != WORD)
	{
		printf("minishell: syntax error: unexpected end token\n");
		return (false);
	}
	return (true);
}
