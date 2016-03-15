/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 14:57:53 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/15 16:35:11 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(char **env)
{
	char	*home;
	char	*user;
	char	buf[100];

	getcwd(buf, 100);
	home = get_env_content(env, "HOME");
	user = get_env_content(env, "USER");
	if (user)
	{
		ft_putstr("# ");
		ft_putstr(user);
	}
	ft_putstr(" in ");
	if (home && ft_strstr(buf, home))
	{
		ft_putchar('~');
		ft_putstr(ft_strstr(buf, home) + ft_strlen(home));
	}
	else
		ft_putstr(buf);
	write(1, " \n$> ", 5);
	ft_strdel(&home);
	ft_strdel(&user);
}
