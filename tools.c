/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 11:07:01 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/17 16:55:33 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (path && (cmd_path = get_cmd_path(cmd_tmp[0], path)))
				exe_fork(env, cmd_tmp, cmd_path);
			else
				ft_putendl("error fork_redirection()");
			free_fork(cmd_tmp, path, cmd_path, path_str);
		}
	}
}
/*
 * * strdup functions
 */

int		ft_occ_nb(char *s, char c)
{
	int count;

	if (s && c)
	{
		count = 0;
		while (*s)
		{
			if (*s == c)
				count++;
			s++;
		}
		return (count);
	}
	return (0);
}

static char	*ft_strndup(char *s1, int len)
{
	char *s2;

	if (!(s2 = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	return (ft_strncpy(s2, s1, len));
}

char	*ft_strcdup(char *s, char c)
{
	int	i;

	if (s && c)
	{
		i = 0;
		while (s[i] && s[i] != c)
			i++;
		return (ft_strndup(s, i));
	}
	return (NULL);
}
