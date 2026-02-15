/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 22:07:08 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 00:16:04 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tok(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr->next)
	{
		free(curr);
		curr = curr->next;
	}
}
