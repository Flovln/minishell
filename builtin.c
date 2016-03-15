/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 14:45:40 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 09:18:54 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * Check builtin
 */

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "setenv"))
		return (2);
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (3);
	else if (!ft_strcmp(cmd, "env"))
		return (4);
	else
		return (0);
}

/*
 * * cd command
 */

void	do_cd(char **cmd, char **env)
{
	DIR				*dir;
	struct stat		st;
	char			*home;

	dir = NULL;
	if (cmd[1])
	{
		dir = opendir(cmd[1]);
		if (stat(cmd[1], &st) == -1)
			ft_putendl_fd(ft_strjoin("cd: No such file or directory: ", cmd[1]), 2);
		else if (!(S_ISDIR(st.st_mode)))
			ft_putendl_fd(ft_strjoin("cd: Not a directory: ", cmd[1]), 2);
		else
			chdir(cmd[1]);
		if (dir)
			closedir(dir);
	}
	else if (!cmd[1])
	{
		home = get_env_content(env, "HOME");
		chdir(home);
		ft_strdel(&home);
	}
}	

/*
 * * Buitin Manager
 */

char	**do_builtin(char **cmd, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	if (!ft_strcmp(cmd[0], "cd"))
		do_cd(cmd, env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		new_env = do_setenv(env, cmd);
//printf("new_env -> |%s|\n", new_env[i]);
	else
	{
		new_env = do_env(env, cmd);
	}
//	return (new_env);
	return (env);
}
