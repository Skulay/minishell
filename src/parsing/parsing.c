/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:54:48 by alehamad          #+#    #+#             */
/*   Updated: 2026/02/16 02:48:23 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(t_token *token)
{
	if (!token)
		return (0);
	if (!check_error(token))
		return (0);
	if (!check_tok(token))
		return (0);
	return(1);
}

// verif de tout les type ERROR
// verif faite atm -> commencer et finir par WORD sans duplication d'op a la suite

// ajouter les commande dans une struct et les op pour savoir que faire avec quoi
// cherche a comment implementer ca
// voir avec tarek qui s'occupe de l'exec pour etre corda

// voir pour clean proprement ! atm on a juste token de malloc
