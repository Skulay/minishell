/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:54:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 03:15:58 by alehamad         ###   ########.fr       */
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
			add_redir(curr, token);
		else if (token->type == PIPE)
		{
			curr->next = init_cmd();
			curr = curr->next;
		}
		token = token->next;
	}
	return (head);
}

int	parsing(t_token *token)
{
	if (!token)
		return (0);
	if (!check_error(token))
		return (0);
	if (!check_tok(token))
		return (0);
	return(1);
}

// verif de tout les type ERROR
// verif faite atm -> commencer et finir par WORD sans duplication d'op a la suite

// ajouter les commande dans une struct et les op pour savoir que faire avec quoi
// cherche a comment implementer ca
// voir avec tarek qui s'occupe de l'exec pour etre corda

// voir pour clean proprement ! atm on a juste token de malloc
