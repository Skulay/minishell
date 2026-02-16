/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:54:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 06:46:26 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*parse_cmd(t_token *token)
{
	t_cmd	*head;
	t_cmd	*curr;

	head = init_cmd();
	curr = head;
	while (token)
	{
		if (token->type == WORD)
			add_arg(curr, token->value);
		else if (is_redir(token->type))
		{
			add_redir(curr, token);
			token = token->next;
		}
		else if (token->type == PIPE)
		{
			curr->next = init_cmd();
			curr = curr->next;
		}
		token = token->next;
	}
	return (head);
}

t_cmd	*parsing(t_token *token)
{
	t_cmd	*cmd;

	if (!token)
		return (NULL);
	if (!check_error(token))
		return (NULL);
	if (!check_tok(token))
		return (NULL);
	cmd = parse_cmd(token);
	if (!cmd)
		return (NULL);
	free_tok(token);
	return (cmd);
}
