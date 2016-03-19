/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:05:53 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/19 17:30:08 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	free_fork(char **cmd_tmp, char **path, char *cmd_path, char *path_str)
{
//	printf("----> FREE FORK START <----\n");
//	free_tab(cmd_tmp);
	free_tab(path);
	ft_strdel(&cmd_path);
	ft_strdel(&path_str);
//	printf("----> FREE FORK END <----\n");
}
*/
void	free_tab(char **tab)
{
	int i;
	int len;

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
