/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 12:09:28 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 15:46:57 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Remove str if it exists in env
 */

static char		**remove_str(char **env, char **new_env, int i, int len)
{
	int j;

	j = 0;
	while (j < i)
	{
		new_env[j] = ft_strdup(env[j]);
		j++;
	}
	while (j < len && env[j + 1])
	{
		new_env[j] = ft_strdup(env[j + 1]);
		j++;
	}
	new_env[j] = NULL;
	free_tab(env);
	return (new_env);
}

static char		**unset_env(char **env, int len, int i)
{
	char **new_env;

	new_env = NULL;
	if (len == 1)
	{
		free_tab(env);
		return (NULL);
	}
	if (!(new_env = (char **)malloc(sizeof(char *) * (len))))
		exit(1);
	new_env = remove_str(env, new_env, i, len);
	return (new_env);
}

char			**do_unsetenv(char **env, char **cmd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_tablen(env);
	if (ft_tablen(cmd) < 2)
		ft_putendl_fd("error: too few arguments", 2);
	else if ((i = is_include(env, cmd[1])) != len && len > 0)
	{
		env = unset_env(env, len, i);
		return (env);
	}
	return (env);
}
