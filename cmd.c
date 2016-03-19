/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:33:17 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 20:06:44 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
 * * Used for fork_redirection when different commands are passed w/ stdin ex. |env -i ls -l |
 */

char			**resize_cmd(char **cmd, char **cmd_tmp, int flag)
{
	while (cmd[flag])
	{
		*cmd_tmp = ft_strdup(cmd[flag]);
		flag++;
		cmd_tmp++;
	}
	*cmd_tmp = NULL;
	return (cmd_tmp);
}

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
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(*path));
					}
			closedir(dir);
			path++;
		}
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	return (NULL);
}

static void		exe_fork_error(char **cmd)
{
	ft_putstr_fd("error: permission denied: ", 2);
	ft_putendl_fd(cmd[0], 2);
}

void			exe_fork(char **env, char **cmd, char *cmd_path)
{
	pid_t	pid;
	char	*tmp;
	char	*rights;

	tmp = ft_strjoin(cmd_path, "/");
	rights = ft_strjoin(tmp, cmd[0]);
	if (access(rights, X_OK) != -1)
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
		exe_fork_error(cmd);
	ft_strdel(&tmp);
	ft_strdel(&rights);
	free_tab(cmd);
}

void			manage_exe_cmd(char **env, char **cmd, char **path)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	cmd_path = NULL;
	if ((ft_strstr(cmd[0], "/")))
	{
		printf("cmd[0] -> |%s|\n", cmd[0]);
		tmp = cmd[0];
		printf("tmp -> |%s|\n", tmp);
		i = ft_strlen(cmd[0]);
		printf("i -> |%d|\n", i);
		while (i > 0 && cmd[0][i] != '/')
			i--;
		cmd_path = ft_strsub(tmp, 0, i);
		cmd[0] = ft_strsub(tmp, i + 1, ft_strlen(tmp));
		ft_strdel(&tmp);
		exe_fork(env, cmd, cmd_path);
	}
	else if ((cmd_path = get_cmd_path(cmd[0], path)) != NULL)
		exe_fork(env, cmd, cmd_path);
//	ft_strdel(&cmd_path);
}
