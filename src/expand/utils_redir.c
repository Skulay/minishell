/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:42:39 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 13:21:18 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	heredoc_not_quoted(t_redir *redir)
{
	if (redir->type == HEREDOC && redir->quote == 0)
		return (1);
	return (0);
}

char	*rm_quotes(char *str)
{
	int			i;
	t_expand	state;
	char		*result;

	i = 0;
	state = NORMAL;
	result = ft_strdup("");
	while (str[i])
	{
		if (state == NORMAL && str[i] == '\'')
			state = SOLO_QUOTE;
		else if (state == NORMAL && str[i] == '"')
			state = DUAL_QUOTE;
		else if (state == SOLO_QUOTE && str[i] == '\'')
			state = NORMAL;
		else if (state == DUAL_QUOTE && str[i] == '"')
			state = NORMAL;
		else
			result = add_char(result, str[i]);
		i++;
	}
	return (result);
}

char	*add_var(char *res, char *str, int *i, t_data *env)
{
	char	*var;
	char	*value;
	int		start;

	(*i)++;
	if (str[*i] == '?')
	{
		value = ft_itoa(env->last_exit_code);
		res = add_str(res, value);
		free(value);
		return (res);
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (add_char(res, '$'));
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_value(env, var);
	if (value)
		res = add_str(res, value);
	free(var);
	(*i)--;
	return (res);
}

void	handle_char(t_exstruct *ex, char *str)
{
	if (ex->state == NORMAL && str[ex->i] == '\'')
		ex->state = SOLO_QUOTE;
	else if (ex->state == NORMAL && str[ex->i] == '"')
		ex->state = DUAL_QUOTE;
	else if (ex->state == SOLO_QUOTE && str[ex->i] == '\'')
		ex->state = NORMAL;
	else if (ex->state == DUAL_QUOTE && str[ex->i] == '"')
		ex->state = NORMAL;
	else if (str[ex->i] == '$' && ex->state != SOLO_QUOTE)
		ex->result = add_var(ex->result, str, &ex->i, ex->env);
	else
		ex->result = add_char(ex->result, str[ex->i]);
}

char	*expand_var_quote(char *str, t_data *env)
{
	t_exstruct	ex;

	ex.i = 0;
	ex.state = NORMAL;
	ex.make_split = 0;
	ex.result = ft_strdup("");
	ex.env = env;
	while (str[ex.i])
	{
		handle_char(&ex, str);
		ex.i++;
	}
	return (ex.result);
}
