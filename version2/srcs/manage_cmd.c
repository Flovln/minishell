/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 12:05:48 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:02:04 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

char	*get_cmd_path(char *cmd, char **paths)
{
	struct dirent	*ret;
	DIR				*dir;
	int				j;

	if (cmd && paths && *paths)
	{
		j = 0;
		while (*paths)
		{
			if ((dir = opendir(*paths)))
			{
				while ((ret = readdir(dir)))
					if (!ft_strcmp(ret->d_name, cmd))
					{
						closedir(dir);
						return (ft_strdup(*paths));
					}
				closedir(dir);
			}
			paths++;
		}
	}
	return (NULL);
}

void	execute_full_path(t_lst *list, char **cmd, char *cmd_path)
{
	int i;

	i = ft_strlen(cmd[0]);
	while (i > 0 && cmd[0][i] != '/')
			i--;
	cmd_path = ft_strsub(cmd[0], 0, i);
	cmd[0] = ft_strsub(cmd[0], i + 1, ft_strlen(cmd[0]));
//	ft_strdel(&cmd_tmp);
	do_fork(list, cmd, cmd_path);
}

void	execute_cmd_handl(t_lst *list, char **cmd, char **paths)
{
	char *cmd_path;

	cmd_path = NULL;
	cmd_path = get_cmd_path(cmd[0], paths);
	if (ft_strstr(cmd[0], "/")) // if <path> + <cmd>
		execute_full_path(list, cmd, cmd_path);
	else // <cmd> alone
		do_fork(list, cmd, cmd_path);
}

void	manage_cmd(t_lst *list, char **cmd, char **paths)
{
	if (check_is_builtin(cmd[0]) > 0)
		do_builtins(list, cmd);
	else
		execute_cmd_handl(list, cmd, paths);
//	free_tab(paths);
}
