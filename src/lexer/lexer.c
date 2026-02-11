/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:33:21 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/11 13:19:17 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_type	what_type(char *str, char c, char d)
{
	if (is_word(str))
		return (WORD);
	if (is_append(c, d))
		return (APPEND);
	if (is_heredoc(c, d))
		return (HEREDOC);
	if (is_redir_in(c))
		return (REDIR_IN);
	if (is_redir_out(c))
		return (REDIR_OUT);
	if (is_pipe(c))
		return (PIPE);
}

t_token	lexer(char *line)
{

}



// example : grep " " | cat -e > outfile

// input origine	|->	[ grep " " ][ | ][ cat -e ][ > ][ outfile ]

// apres lexer		|->	[WORD][PIPE][WORD][REDIR_OUT][WORD]
