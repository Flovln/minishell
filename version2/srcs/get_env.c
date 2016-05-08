/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 10:42:27 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:01:41 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

char		*get_var_content(char *str)
{
	char	*var_content;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	i += 1;
	if (i == j)
		return (NULL); //no content
	else
		var_content = ft_strsub(str, i, j);
	return (var_content);
}

char		*get_var_name(char *str)
{
	char	*var_name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	j += 1;
	var_name = ft_strsub(str, i, j);
	return (var_name);
}

t_lst		*create_node(char **env)
{
	t_lst *new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->content = get_var_content(*env);
	new->name = get_var_name(*env);
	new->next = NULL;
	return (new);
}

void		list_push_node(t_lst **head, t_lst *new_node)
{
	t_lst *cur;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
}
