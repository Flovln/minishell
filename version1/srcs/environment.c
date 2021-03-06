/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:16:11 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/22 13:29:39 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**do_env(char **env, char **cmd)
{
	char **tmp;

	tmp = NULL;
	if (ft_tablen(cmd) == 1)
	{
		print_env(env);
		return (env);
	}
	if (env)
		tmp = tab_dup(env);
	env = manage_do_env(env, cmd, tmp);
	return (env);
}

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
				start = ft_strlen(str);
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
