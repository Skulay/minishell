/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:34:36 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 00:12:40 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_error(t_token *token)
{
	t_token	*curr;

	curr = token;
	if (curr->type != WORD)
		return (1);
	while (curr->next)
	{
		curr = curr->next;
		if (token->type == ERROR)
			return (true);
	}
	return (false);
}

bool	check_order(t_token *token)
{
	t_token	*curr;
	int		count;

	curr = token;
	count = 0;
	while (curr->next)
	{
		while (curr->type == WORD && curr->next)
		{
			curr = curr->next;
			count++;
		}
		if (curr->type != WORD && curr->next)
		{
			curr = curr->next;
			count++;
		}
	}
	if (count % 2 == 1)
		return (false);
	else
		return (true);
}
