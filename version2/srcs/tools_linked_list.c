/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 14:36:38 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:02:26 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

int         check_var_exists(t_lst *list, char *var_name)
{
	while (list)
	{
		if (!ft_strcmp(list->name, var_name))
			return (1);
		list = list->next;
	}
	return (0);
}

char	*get_content(t_lst *list, char *str)
{
	char *content;

	content = NULL;
	while (list)
	{
		if (!ft_strcmp(list->name, str))
			content = ft_strdup(list->content);
		list = list->next;
	}
	return (content);
}
