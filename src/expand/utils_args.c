/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:09:07 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 13:00:38 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*extract_var(char *str, int *i, t_data *data)
{
	char	*var;
	char	*value;
	int	start;

	(*i)++;
	if (str[*i] == '?')
		return (ft_itoa(data->last_exit_code));
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
	{
		(*i)--;
		return (ft_strdup("$"));
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = get_env_value(data, var);
	free(var);
	if (!value)
		value = ft_strdup("");
	(*i)--;
	return (value);
}

void	handle_dollar(t_exstruct *ex, char *str, t_data *data)
{
	char *value;

	value = extract_var(str, &ex->i, data);

	if (ex->state == NORMAL && value && ft_strchr(value, ' '))
		ex->make_split = 1;

	ex->result = add_str(ex->result, value);
	free(value);
}

char	*expand_with_flag(char *str, t_data *data, int *make_split)
{
	t_exstruct ex;

	ex.i = 0;
	ex.state = NORMAL;
	ex.make_split = 0;
	ex.result = ft_strdup("");
	while (str[ex.i])
	{
		if (ex.state == NORMAL && str[ex.i] == '\'')
			ex.state = SOLO_QUOTE;
		else if (ex.state == NORMAL && str[ex.i] == '"')
			ex.state = DUAL_QUOTE;
		else if (ex.state == SOLO_QUOTE && str[ex.i] == '\'')
			ex.state = NORMAL;
		else if (ex.state == DUAL_QUOTE && str[ex.i] == '"')
			ex.state = NORMAL;
		else if (str[ex.i] == '$' && ex.state != SOLO_QUOTE)
			handle_dollar(&ex, str, data);
		else
			ex.result = add_char(ex.result, str[ex.i]);
		ex.i++;
	}
	*make_split = ex.make_split;
	return (ex.result);
}

char **expand_split(char *str, t_data *data)
{
	char	*expanded;
	char	**result;
	int		make_split;

	make_split = 0;
	expanded = expand_with_flag(str, data, &make_split);

	if (make_split)
		result = ft_split(expanded, ' ');
	else
		result = single_to_tab(expanded);

	free(expanded);
	return (result);
}

char	**append_all(char **dest, char **src)
{
	char	**new;
	int		i;
	int		j;
	int		ldest;
	int		lsrc;

	ldest = tab_len(dest);
	lsrc = tab_len(src);
	new = malloc(sizeof(char *) * (ldest + lsrc + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < ldest)
		new[i] = dest[i];
	j = -1;
	while (++j < lsrc)
		new[i + j] = ft_strdup(src[j]);
	new[i + j] = NULL;
	free(dest);
	return (new);
}
