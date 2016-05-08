/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 13:45:59 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/02 09:15:24 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

void	update_var_content(t_lst *list, char *var_name, char *str)
{
	while (list)
	{
		if (!ft_strcmp(list->name, var_name))
		{
			ft_strdel(&(list->content));
			list->content = ft_strdup(str);
		}
		list = list->next;
	}
}

static void		manage_setenv_args(t_lst *list, char **cmd, int len)
{
	if (len == 2)
		if (check_var_exists(list, cmd[1]))
			update_var_content(list, cmd[1], "");
		else
			list_push_node(&list, create_node(&cmd[1]));
	else if (len == 3)
		if (check_var_exists(list, cmd[1]))
			update_var_content(list, cmd[1], cmd[2]);
		else
		{
			cmd[1] = ft_strjoin(cmd[1], cmd[2]);
			list_push_node(&list, create_node(&cmd[1]));
		}
	else
		ft_putendl_fd("setenv: Too many arguments.", 2);
}

static void		manage_env_setenv(t_lst *list, char **cmd)
{
	int 	i;

	i = 1;
	while (cmd[i])
	{
		printf("test\n");
/*		if (check_var_exists(list, cmd[i]))
		{
			//split cmd[i] to get new content
			printf("cmd[i] |%s|\n", cmd[i]);//test
			update_var_content(list, cmd[i], ""); //test tmp
		}
		else
		{*/
			list_push_node(&list, create_node(&cmd[i]));
			cmd[i] = ft_strcat(cmd[i], "\n");
			i++;
//		}
	}
	do_print_env(list);
}

void			do_setenv(t_lst *list, char **cmd, int flag)
{
	int	len;

	len = ft_tablen(cmd);
	if (len == 1)
		do_print_env(list);
	else if (flag == 1 && !check_is_alpha(cmd[1]))
	{
		cmd[1] = ft_strcat(cmd[1], "=");
		manage_setenv_args(list, cmd, len);
	}
	else if (flag == 2)
		manage_env_setenv(list, cmd);
}
