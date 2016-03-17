/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:07:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/16 16:48:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * * checks if var passed as parameter already exists in env / 
 * * i is incremented so we know were to replace an existing Var (updated) /
 * * or add new one at the end
 */

int		is_include(char **env, char *cmd)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			break ;
		i++;
	}
	return (i);
}

/*
 * * Function Duplicating tab
 */

char	**tab_dup(char **tab)
{
	char	**tmp;
	int		i;
	int		len;

	if (tab)
	{
		i = 0;
		len = ft_tablen(tab);
		if (!(tmp = (char **)malloc(sizeof(char *) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			tmp[i] = ft_strdup(tab[i]);
			i++;
		}
		tmp[i] = NULL;
		return (tmp);
	}
	return (NULL);
}

/*
 * * Function getting command's path entered through stdin
 */

char	*get_cmdpath(char *cmd, char **path)
{
	int				j;
	DIR				*dir;
	struct dirent	*ret;

	if (cmd && path && *path)
	{
		j = 0;
		while (*path)
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
	return (NULL);
}

/*
 * * Functions managing different arguments when using env -.. .. ..
 */

char	**resize_cmd(char **cmd, char **cmd_tmp, int flag)
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

void	fork_redirection(char **env, char **cmd, int flag)
{
	char	*cmd_path;
	char	*path_str;
	char	**path;
	char	**cmd_tmp;

	cmd_path = NULL;
	if (!(cmd_tmp = (char **)malloc(sizeof(char *) *
				(ft_tablen(cmd) - flag + 1))))
		return ;
	if (env && (cmd_tmp = resize_cmd(cmd, cmd_tmp, flag)))
	{
		path_str = get_env_content(env, "PATH");
		if (path_str && (path = ft_strsplit(path_str, ':')))
		{
			if (path && (cmd_path = get_cmdpath(cmd_tmp[0], path)))
				exe_fork(env, cmd_tmp, cmd_path);
			else
				ft_putendl("error fork_redirection()");
			free_fork(cmd_tmp, path, cmd_path, path_str);
		}
	}
}

/*
int		ft_multi_strcmp(char *s, char *s1, char *s2)
{
	if (!ft_strcmp(s, s1) || !ft_strcmp(s, s2))
		return (1);
	return (0);
}*/

/*
 * * Free functions
 */

void	free_fork(char **cmd_tmp, char **path, char *cmd_path, char *path_str)
{
	free_tab(cmd_tmp);
	free_tab(path);
	ft_strdel(&cmd_path);
	ft_strdel(&path_str);
}

void	free_tab(char **tab)
{
	int	i;
	int	len;

	if (tab)
	{
		if (*tab)
		{
			i = 0;
			len = ft_tablen(tab);
			while (i < len)
			{
				ft_strdel(&tab[i]);
				i++;
			}
		}
		free(tab);
		tab = NULL;
	}
}
/*
void            free_ptr(char **env_cpy, char **cmd, char **path_cpy)
{
//	ft_strdel(env_cpy);
	ft_strdel(cmd);
//	ft_strdel(path_cpy);
}*/
