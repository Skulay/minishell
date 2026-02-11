/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_type2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:29:12 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/11 13:07:29 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_word(char *str)
{
	int i;

	i = 0;
	while (ft_isalnum(str[i]))
	{
		if (str[i + 1] == '\0')
			return (true);
		i++;
	}
	return (false);
}

bool	is_append(char c, char d)
{
	if (c == '>' && d == '>')
		return (true);
	return (false);
}

bool	is_heredoc(char c, char d)
{
	if (c == '<' && d == '<')
		return (true);
	return (false);
}

bool	is_in_quote(char *str)
{
	int	after;
	int	before;
	int	i;
	int	j;

	j = 0;
	i = 0;
	before = 0;
	after = 0;
	while (str[i])
	{
		i++;
	}
}




//c'est le premier char et d c'est le char d'apres

// sert a savoir si >> et << (il faut les mettre avant les is_redir_in/out, question de prioriter)
