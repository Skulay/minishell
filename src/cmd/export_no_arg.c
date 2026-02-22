/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:59:58 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/22 19:29:50 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// les valeur return
// gerer les arg apres export actuellement rien est gerer
//

int	ft_strcmp_equal(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	ft_print_export(char **export)
{
	int	i;

	i = 0;
	while (export[i])
	{
		printf("declare -x %s\n", export[i]);
		i++;
	}
}

void	ft_sort_char_tab(char **export)
{
	int		i;
	int		swp;
	char	*tmp;

	if (!export)
		return ;
	swp = 1;
	while (swp)
	{
		swp = 0;
		i = 0;
		while (export[i] && export[i + 1])
		{
			if (ft_strcmp_equal(export[i], export[i + 1]) > 0)
			{
				tmp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = tmp;
				swp = 1;
			}
			i++;
		}
	}
}

void	ft_strcpy(char *dst, char *src)
{
	int	i;
	int	j;
	int	equal;

	i = 0;
	j = 0;
	equal = 0;
	while (src[i])
	{
		dst[j++] = src[i];
		if (src[i] == '=' && !equal)
		{
			dst[j++] = '\"';
			equal = 1;
		}
		i++;
	}
	if (equal)
		dst[j++] = '\"';
	dst[j] = '\0';
}

int	ft_export_no_arg(t_data *data)
{
	int		i;
	char	**export;

	i = 0;
	export = malloc(sizeof(char *) * (tab_len(data->my_env) + 1));
	if (!export)
		return (1);
	while (data->my_env[i])
	{
		export[i] = malloc(sizeof(char) * (strlen(data->my_env[i]) + 3));
		if (!export[i])
		{
			free_tab(export);
			return (1);
		}
		ft_strcpy(export[i], data->my_env[i]);
		i++;
	}
	export[i] = NULL;
	ft_sort_char_tab(export);
	ft_print_export(export);
	free_tab(export);
	return (0);
}
