/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:58:18 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/18 02:47:30 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// unset with no options

char	**ft_unset(t_data *data, char *unset)
{
	int		i;
	char	**new;

	i = tab_len(data->my_env);
	new = malloc(sizeof(char *) * i); // pas de +1 pour reduire de 1 la taille


	free_tab(data->my_env);
	data->my_env = new;
}
