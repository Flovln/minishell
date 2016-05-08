/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 17:48:02 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 17:59:58 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

int		check_is_builtin(char *cmd)
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

void	do_print_env(t_lst *list)
{
	while (list)
	{
		if (!list->name)
			list = list->next;
		ft_putstr(list->name);
		if (list->content)
			ft_putendl(list->content);
		else
			ft_putchar('\n');
		list = list->next;
	}
}

void	do_builtins(t_lst *list, char **cmd) //, char **paths)
{
	t_lst	*new_list;

	new_list = NULL;
	if (check_is_builtin(cmd[0]) == 1)
		do_cd(list, cmd);
	if (check_is_builtin(cmd[0]) == 2)
		do_setenv(list, cmd, 1);
	else if (check_is_builtin(cmd[0]) == 3)
		do_unsetenv(list, cmd);
	else if (check_is_builtin(cmd[0]) == 4)
		do_env(list, cmd); //, paths);
}
