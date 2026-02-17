/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 12:57:33 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/17 13:36:02 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**single_to_tab(char *str)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup(str);
	tab[1] = NULL;
	return (tab);
}

char	*add_char(char *str, char c)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 2));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(str);
	return (res);
}

char	*add_str(char *res, char *add)
{
	char	*new;

	if (!add)
		return (res);
	if (!res)
		return (ft_strdup(add));
	new = ft_strjoin(res, add);
	free(res);
	return (new);
}

char	*my_get_env(t_data *data, char *var)
{
	int	i;
	int	len;

	if (!data->my_env || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], var, len) == 0
			&& data->my_env[i][len] == '=')
			return (data->my_env[i] + len + 1);
		i++;
	}
	return (NULL);
}
