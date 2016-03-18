/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:16:11 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 17:22:32 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	if (env && *env)
		while (*env)
		{
			ft_putendl(*env);
			env++;
		}
	else
		ft_putendl_fd("empty environment", 2);
}

/*
 * * Function used for env -i option
 */

char	**ignore_env(char **env, int len)
{
	if (len != 2)
	{
		ft_putendl_fd("error: too few arguments", 2);
		return (env);
	}
	return (NULL);
}

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
