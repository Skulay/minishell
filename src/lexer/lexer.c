/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:33:21 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/27 01:28:34 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_close_or_not(char *line)
{
	int	single;
	int	dual;
	int	i;

	single = 0;
	dual = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !dual)
			single = !single;
		else if (line[i] == '\"' && !single)
			dual = !dual;
		i++;
	}
	return (single || dual);
}

t_type	what_type(char c, char d)
{
	if (is_error_syntax(c, d))
		return (ERROR);
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
	return (WORD);
}

char	*get_operator(char *line, int *i)
{
	char	*value;

	if (is_append(line[*i], line[*i + 1]))
	{
		value = ft_substr(line, *i, 2);
		*i += 2;
	}
	else if (is_heredoc(line[*i], line[*i + 1]))
	{
		value = ft_substr(line, *i, 2);
		*i += 2;
	}
	else if (is_error_syntax(line[*i], line[*i + 1]))
	{
		value = ft_substr(line, *i, 2);
		*i += 2;
	}
	else
	{
		value = ft_substr(line, *i, 1);
		(*i)++;
	}
	return (value);
}

char	*get_word(char *line, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i] == quote)
				(*i)++;
		}
		else if (is_space(line[*i]) || is_operator(line[*i]))
			break ;
		else
			(*i)++;
	}
	return (ft_substr(line, start, *i - start));
}

t_token	*lexer(char *line, t_data *data)
{
	t_token	*tokens;
	char	*val;
	int		i;

	tokens = NULL;
	i = 0;
	if (quote_close_or_not(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		data->last_exit_code = 2;
		return (NULL);
	}
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			val = get_operator(line, &i);
		else
			val = get_word(line, &i);
		ft_tokadd_back(&tokens, ft_toknew(val, what_type(val[0], val[1])));
	}
	return (tokens);
}
