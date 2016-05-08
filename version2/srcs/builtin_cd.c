/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/29 16:15:28 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/02 14:25:56 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

static void		do_user_root(t_lst *list)
{
	char	buf[512];
	t_lst	*tmp;

	tmp = list;
	while (list)
	{
		if (ft_strcmp(list->name, "HOME=") == 0)
		{
			if (getcwd(buf, 512) != NULL)
				update_var_content(list, "OLDPWD=", getcwd(buf, 512));
			chdir(list->content);
			update_var_content(tmp, "PWD=", getcwd(buf, 512));
		}
		list = list->next;
	}
}

static void		do_switch_pwd(t_lst *list)
{
	char	buf[512];
	char	*tmp;
	t_lst	*list_tmp;

	list_tmp = list;
	while (list_tmp)
	{
		if (ft_strcmp(list_tmp->name, "OLDPWD=") == 0)
		{
			tmp = list_tmp->content;
			if (getcwd(buf, 512) != NULL)
				update_var_content(list_tmp, "OLDPWD=", getcwd(buf, 512));
			chdir(tmp);
			update_var_content(list, "PWD=", getcwd(buf, 512));
		}
		list_tmp = list_tmp->next;
	}
}

static void		manage_error(char **cmd, t_lst *list)
{
	struct stat st;
	char		buf[512];

	if (stat(cmd[1], &st) == -1)
	{
		ft_putstr_fd("cd: No such file or directory: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else if (!(S_ISDIR(st.st_mode)))
	{
		ft_putstr_fd("cd: Not a directory: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else if (access(cmd[1], X_OK) == -1)
	{
		ft_putstr_fd("cd: Permission denied: ", 2);
		ft_putendl_fd(cmd[1], 2);
	}
	else
	{
		update_var_content(list, "OLDPWD=", getcwd(buf, 512));
		chdir(cmd[1]);
		update_var_content(list, "PWD=", getcwd(buf, 512));
	}
}

void			do_cd(t_lst *list, char **cmd)
{
	int		len;
	DIR		*dir;

	dir = NULL;
	len = ft_tablen(cmd);
	if (!cmd[1] || (!ft_strcmp(cmd[1], "~")))
		do_user_root(list);
	else if (len > 2)
		ft_error("cd: Too many arguments", 0);
	else if (!ft_strcmp(cmd[1], "-"))
		do_switch_pwd(list);
	else
		manage_error(cmd, list);
}
