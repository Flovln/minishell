/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:33:17 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/22 13:41:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*get_cmd_path(char *cmd, char **path)
{
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path && *path)
	{
		j = 0;
		while (*path)
		{
			if ((dir = opendir(*path)))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(*path));
					}
				closedir(dir);
			}
			path++;
		}
	}
	return (NULL);
}

static void		norights_error(char **env, char **cmd, char *tmp)
{
	if (access(cmd[0], X_OK) == -1 && is_in(env, cmd[0]))
	{
		ft_putstr_fd("error: permission denied: ", 2);
		ft_putendl_fd(cmd[0], 2);
	}
	else
		ft_putendl_fd("command not found", 2);
	ft_strdel(&tmp);
	free_tab(cmd);
}

void			exe_fork(char **env, char **cmd, char *cmd_path)
{
	pid_t	pid;
	char	*tmp;

	tmp = NULL;
	if (cmd_path)
		tmp = ft_strjoin(cmd_path, "/");
	else
		tmp = ft_strdup("./");
	if (access(ft_strjoin(tmp, cmd[0]), X_OK) != -1)
	{
		pid = fork();
		if (pid > 0)
			wait(0);
		else if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			ft_strdel(&cmd_path);
			cmd_path = ft_strjoin(tmp, cmd[0]);
			ft_strdel(&tmp);
			execve(cmd_path, cmd, env);
		}
	}
	else
		norights_error(env, cmd, tmp);
}

static void		manage_error(char **cmd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd[0], 2);
}

void			manage_exe_cmd(char **env, char **cmd, char **path)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	cmd_path = NULL;
	if (cmd[0][2] != '/')
	{
		if ((ft_strstr(cmd[0], "/") && ft_strlen(cmd[0]) > 1))
		{
			tmp = cmd[0];
			i = ft_strlen(cmd[0]);
			while (i > 0 && cmd[0][i] != '/')
				i--;
			cmd_path = ft_strsub(tmp, 0, i);
			cmd[0] = ft_strsub(tmp, i + 1, ft_strlen(tmp));
			ft_strdel(&tmp);
			exe_fork(env, cmd, cmd_path);
		}
		else if ((cmd_path = get_cmd_path(cmd[0], path)) != NULL)
			exe_fork(env, cmd, cmd_path);
		else
			manage_error(cmd);
	}
}
