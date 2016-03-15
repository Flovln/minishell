/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:07:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 14:44:59 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * checks if var passed as parameter already exists in env / 
 * * i is incremented so we know were to replace an existing Var (updated) /
 * * or add new one at the end
 */

int		is_include(char **env, char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			break ;
		i++;
	}
	return (i);
}

/*
 * * Function Duplicating tab
 */

char	**tab_dup(char **tab)
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

/*
 * * Function Freeing **tab
 */

void	free_tab(char **tab)
{
	int	i;
	int	len;

	if (tab)
	{
		if (*tab)
		{
			i = 0;
			len = ft_tablen(tab);
			while (i < len)
			{
				ft_strdel(&tab[i]);
				i++;
			}
		}
		free(tab);
		tab = NULL;
	}
}
