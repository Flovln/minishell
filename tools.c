/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:07:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/20 13:09:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**tab_dup(char **tab)
{
	char	**tmp;
	int		i;
	int		len;

	if (tab)
	{
		i = 0;
		len = ft_tablen(tab);
		if (!(tmp = (char **)malloc(sizeof(char *) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			tmp[i] = ft_strdup(tab[i]);
			i++;
		}
		tmp[i] = NULL;
		return (tmp);
	}
	return (NULL);
}

int				ft_occ_nb(char *s, char c)
{
	int count;

	if (s && c)
	{
		count = 0;
		while (*s)
		{
			if (*s == c)
				count++;
			s++;
		}
		return (count);
	}
	return (0);
}

static char		*ft_strndup(char *s1, int len)
{
	char *s2;

	if (!(s2 = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_strncpy(s2, s1, len));
}

char			*ft_strcdup(char *s, char c)
{
	int	i;

	if (s && c)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		return (ft_strndup(s, i));
	}
	return (NULL);
}
