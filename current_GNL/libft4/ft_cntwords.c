/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cntwords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalsago <amalsago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:18:21 by amalsago          #+#    #+#             */
/*   Updated: 2018/11/21 12:20:11 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_cntwords(char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (!ft_isseparator(s[i], c))
		{
			words++;
			while (!ft_isseparator(s[i], c) && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (words);
}
