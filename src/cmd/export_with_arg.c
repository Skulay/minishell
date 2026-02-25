/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:13:13 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/25 20:56:53 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strlen_key(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

int	find_in_env(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_key(key);
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len)
			&& (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	add_update_env(t_data *data, char *arg)
{
	int		i;
	int		len;
	int		index;
	char	**new_env;

	len = ft_strlen_key(arg);
	index = find_in_env(data->my_env, arg);
	if (index >= 0)
	{
		free(data->my_env[index]);
		data->my_env[index] = ft_strdup(arg);
		return ;
	}
	i = tab_len(data->my_env);
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = -1;
	while (data->my_env[++i])
		new_env[i] = data->my_env[i];
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	free(data->my_env);
	data->my_env = new_env;
}
