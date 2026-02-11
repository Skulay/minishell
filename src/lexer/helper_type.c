/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 09:57:59 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/11 13:18:03 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_delimiter(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '|' || c == '<'
		|| c == '>')
		return (true);
	return (false);
}

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	is_redir_out(char c)
{
	if (c == '>')
		return (true);
	return (false);
}

bool	is_redir_in(char c)
{
	if (c == '<')
		return (true);
	return (false);
}




// while (input[i])
// {
//     if (is_space(input[i]))
//         i++;

//     else if (is_append(input[i], input[i + 1]))
//         add_token(APPEND);

//     else if (is_heredoc(input[i], input[i + 1]))
//         add_token(HEREDOC);

//     else if (is_pipe(input[i]))
//         add_token(PIPE);

//     else if (is_redir_out(input[i]))
//         add_token(REDIR_OUT);

//     else if (is_redir_in(input[i]))
//         add_token(REDIR_IN);

//     else
//         read_word();
// }


// dans read word

// while (input[i] && !is_delimiter(input[i]))
//     i++;
