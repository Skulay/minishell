/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:19:09 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/15 20:06:34 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// a mettre dans le main pour print les token apres lexer

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: ");
		if (tokens->type == WORD)
			printf("WORD");
		else if (tokens->type == PIPE)
			printf("PIPE");
		else if (tokens->type == ERROR)
			printf("ERROR");
		else if (tokens->type == REDIR_IN)
			printf("REDIR_IN");
		else if (tokens->type == REDIR_OUT)
			printf("REDIR_OUT");
		else if (tokens->type == APPEND)
			printf("APPEND");
		else if (tokens->type == HEREDOC)
			printf("HEREDOC");
		printf(" | VALUE: [%s]\n", tokens->value);
		tokens = tokens->next;
	}
}
