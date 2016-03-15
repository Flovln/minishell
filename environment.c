/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:16:11 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 11:16:37 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* * Function getting contents inside env var
*/

char	*get_env_content(char **env, char *str)
{
	int		start;
	char	*tmp;
	char	*content;

	if (env && *env)
	{
		while (*env)
		{
			if (!ft_strncmp(*env, str, ft_strlen(str)))
			{
				start = ft_strlen(str) + 1;
				/* parsing for env variables USER + HOME */
				tmp = ft_strsub(*env, start, ft_strlen(*env) - start);
				content = ft_strdup(tmp);
				ft_strdel(&tmp);
				return (content);
			}
			env++;
		}
	}
	return (NULL);
}
