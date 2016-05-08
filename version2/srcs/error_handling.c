/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 10:53:20 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:01:29 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

int		cmd_in_var(t_lst *list, char *cmd, char *var)
{
	struct dirent	*ret;
	DIR				*dir;
	char			*content;

	content = NULL;
	while (list)
	{
		if (!ft_strcmp(list->name, var))
			content = get_var_content(list->content);
		list = list->next;
	}
	if ((dir = opendir(content)))
		while ((ret = readdir(dir)))
			if (!ft_strcmp(cmd, ret->d_name))
				return (1);
	return (0);
}

void	permissions_error_handl(t_lst *list, char **cmd)
{
	if (access(cmd[0], X_OK) == -1 && cmd_in_var(list, cmd[0], "PWD="))
	{
		ft_putstr_fd("error: permission denied: ", 2);
		ft_putendl_fd(cmd[0], 2);
	}
	else
		ft_putendl_fd("error: command not found", 2);
	//	free_tab(cmd);
}

void	ft_error(char *err, int flag)
{
	ft_putendl_fd(err, 2);
	if (flag == 1)
		exit(1);
}
