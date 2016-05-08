/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 12:55:37 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/22 18:17:04 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**resize_cmd(char **cmd, char **cmd_tmp, int flag)
{
	int i;

	i = 0;
	while (cmd[flag])
	{
		cmd_tmp[i] = ft_strdup(cmd[flag]);
		flag++;
		i++;
	}
	cmd_tmp[i] = NULL;
	return (cmd_tmp);
}

void	fork_bis(char **env, char **cmd_tmp, char *cmd_path, char **path)
{
	char *path_str;

	path_str = NULL;
	path_str = get_env_content(env, "PATH=");
	cmd_path = get_cmd_path(cmd_tmp[0], path);
	if (!path_str && !path)
	{
		if (!ft_strncmp(cmd_tmp[0], "./", 2))
			exe_fork(env, cmd_tmp, NULL);
		else
			ft_putendl_fd("No such file or directory", 2);
	}
	else if (path && cmd_path)
		exe_fork(env, cmd_tmp, cmd_path);
	else if (!ft_strncmp(cmd_tmp[0], "./", 2))
		exe_fork(env, cmd_tmp, NULL);
	else
		ft_putendl_fd("No such file or directory", 2);
}

void	fork_redirection(char **env, char **cmd, int flag)
{
	char *cmd_path;
	char *path_str;
	char **path;
	char **cmd_tmp;

	cmd_path = NULL;
	path = NULL;
	path_str = NULL;
	if (!(cmd_tmp = (char **)malloc(sizeof(char *) *
					(ft_tablen(cmd) - flag + 1))))
		return ;
	path_str = get_env_content(env, "PATH=");
	if (path_str)
		path = ft_strsplit(path_str, ':');
	if ((cmd_tmp = resize_cmd(cmd, cmd_tmp, flag)))
	{
		if (is_builtin(cmd_tmp[0]))
			env = do_builtin(cmd_tmp, env, 0);
		fork_bis(env, cmd_tmp, cmd_path, path);
		free_fork(path, cmd_path, path_str);
	}
	else
		env = do_builtin(cmd_tmp, env, 1);
}
