/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 15:24:40 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/02 11:05:15 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

static void		manage_multi_cmd(t_lst *list, char **cmd)
{
	char **paths_tmp;
	char *cmd_path;

	cmd_path = NULL;
	paths_tmp = parse_path(list);
	cmd_path = get_cmd_path(cmd[3], paths_tmp);
	if (cmd_is_in_path(cmd[3], paths_tmp))
		do_fork(list, cmd + 3, cmd_path);
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd[3], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void			manage_unsetenv(t_lst *list, char **cmd, int len)
{
	if (len == 2)
	{
		ft_putendl_fd("env: option requires an argument -- u", 2);
		ft_putendl_fd("usage: env [-u name]", 2);
	}
	else if (len == 3)
	{
		do_unsetenv(list, cmd);
		do_print_env(list);
	}
	else if (len > 3)
		manage_multi_cmd(list, cmd);
}

void			list_remove_node(t_lst **node, char *varname)
{
	t_lst *tmp;

	tmp = *node;
	if (*node)
	{
		if (!ft_strcmp((*node)->name, varname))
		{
			tmp = *node;
			*node = (*(node))->next;
			ft_strdel(&(tmp->name));
			ft_strdel(&(tmp->content));
			free(tmp);
		}
		list_remove_node(&(*node)->next, varname);
	}
}

void			do_unsetenv(t_lst *list, char **cmd)
{
	int		len;
	int		i;

	i = 0;
	len = ft_tablen(cmd);
	if (len == 1)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else if (len > 1)
	{
		while (cmd[++i])
		{
			if (ft_strcmp(cmd[i], "="))
				cmd[i] = ft_strcat(cmd[i], "=");
			list_remove_node(&list, cmd[i]);
		}
	}
}
