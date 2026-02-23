/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:57:26 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/23 03:38:26 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// ne pas oublier de modifier le PWD et le OLD PWD dans l'env
// get_env_value(data->my_env, "HOME");

char	*get_env_value(t_data *data, char *key)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (data->my_env[i])
	{
		if (ft_strncmp(data->my_env[i], key, len) == 0
			&& data->my_env[i][len] == '=')
			return (data->my_env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	update_env(t_data *data, char *key, char *value)
{
	int		index;
	char	*tmp;
	char	*new;

	index = find_in_env(data->my_env, key);
	if (index < 0)
		return ;
	tmp = ft_strjoin(key, "=");
	new = ft_strjoin(tmp, value);
	free(tmp);
	free(data->my_env[index]);
	data->my_env[index] = new;
}

int	change_dir(t_data *data, char *path)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(oldpwd);
		return (1);
	}
	update_env(data, "OLDPWD", oldpwd);
	update_env(data, "PWD", cwd);
	free(oldpwd);
	free(cwd);
	return (0);
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	if (args[1] && args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	if (!args[1])
		path = get_env_value(data, "HOME");
	else
		path = args[1];
	if (!path)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	return (change_dir(data, path));
}
