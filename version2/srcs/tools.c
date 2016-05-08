/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 16:44:55 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:02:16 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

int		check_is_alpha(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str) == 0)
		{
			ft_putstr_fd("setenv: Variable name must ", 2);
			ft_putendl_fd("contain alphanumeric characters.", 2);
			return (1);
		}
		str++;
	}
	return (0);
}

int		get_list_len(t_lst *list)
{
	int count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}

char	**list_in_tab(t_lst *list)
{
	char	**env_cpy;
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = get_list_len(list);
	if (!(env_cpy = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (list)
	{
		str = ft_strdup(list->name);
		if (list->content)
			str = ft_strjoin(str, list->content);
		env_cpy[i] = str;
		i++;
		list = list->next;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
