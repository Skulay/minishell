/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alehamad <alehamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 03:53:22 by tkhider           #+#    #+#             */
/*   Updated: 2026/03/03 17:44:31 by alehamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_heredoc_expand(char *line)
{
	char	*new_line;
	char	*value;
	int		len;
	int		i;

	free(line);
	return (new_line);
}

// recuperer la value a chercher

// trouver la value

// ajouter la value a une nouvelle string

// cherche la prochaine value vis a vis de la nouvelle string si il y'en a une

//logique pour expand 1 par 1
// $USER test $USER test $USER
// sku test $USER test $USER
// sku test sku test $USER
// sku test sku test sku

//        TEST

// input > test$USERufhrehu
// out   > test

//        TEST2

// input > test $USERufhrehu
// out   > test

//        TEST3

// input > test $USER ufhrehu
// out   > test sku ufhrehu

//        TEST4

// input > test $USER$USER
// out   > test skusku

//        TEST5

// input > test $USER$PWDEW
// out   > test sku

//        TEST6

// input > test $USER$PWDEW salut
// out   > test sku salut

//        TEST7

// input > test $USERFEWFWE$PWD salut
// out   > test /home/sku/projet/minishell salut

// donc faire un tableaux split sur espace
// a chaque tab[i] si c'est une var l'expand et si on trouve pas return le debut du tableaux
// plusieur var a la suite sont accepter

// renvoyer la nouvelle string
