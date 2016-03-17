/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 17:05:03 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 15:47:48 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Testing function()
 */

void			ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	printf("\n-> print_tab() <-\n\n");
	while (tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
	printf("\n-> print_tab() end <-\n\n");
}

/*
 * * Used when setting new env w/ env <varname>=<content>
 */

char			**setenv_redirection(char **env, char **cmd)
{
	char	*cmd_var[4];
	char	**new_env;

	cmd_var[0] = ft_strdup("setenv");
	cmd_var[1] = ft_strcdup(cmd[1], '=');
	cmd_var[2] = ft_strstr(cmd[1], "=");
	cmd_var[2] = ft_strsub(cmd_var[2], 1, ft_strlen(cmd_var[2]) - 1);
	cmd_var[3] = NULL;
	new_env = do_setenv(env, cmd_var);
	ft_strdel(&cmd_var[0]);
	ft_strdel(&cmd_var[1]);
	ft_strdel(&cmd_var[2]);
	return (new_env);
}

/*
 * * Add a new string in env
 */

char			**add_str(char **env, char **new_env, char **cmd, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	tmp = ft_strjoin(cmd[1], "=");
	new_env[i] = ft_strjoin(tmp, cmd[2]);
	ft_strdel(&tmp);
	new_env[i + 1] = NULL;
	return(new_env);
}

/*
 * * modify str if var already exists in env
 */

static char		**update_str(char **env, char **cmd, int i, int len)
{
	char *tmp;

	if (len == 1)
	{
		free_tab(env);
		return (NULL);
	}
	ft_strdel(&env[i]);
	env[i] = ft_strcat(cmd[1], "=");
	tmp = env[i];
	env[i] = ft_strjoin(tmp, cmd[2]);
	return (env);
}

/*
 * * setenv command
 */

char			**do_setenv(char **env, char **cmd)
{
	int		i;
	int		len;
	char	**new_env;

	if (ft_tablen(cmd) != 3)
	{
		ft_putendl_fd("setenv: too few arguments", 2);
		return (env);
	}
	else
	{
		len = ft_tablen(env);
		if ((i = is_include(env, cmd[1])) == len || len == 0)
		{
			if (!(new_env = (char **)malloc(sizeof(char *) * (len + 2))))
				return (NULL);
			new_env = add_str(env, new_env, cmd, len);
			free_tab(env);
			return (new_env);
		}
		new_env = update_str(env, cmd, i, len);
		return (new_env);
	}
	return (NULL);
}
