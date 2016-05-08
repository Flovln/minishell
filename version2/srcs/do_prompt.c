/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:16:41 by fviolin           #+#    #+#             */
/*   Updated: 2016/05/01 18:00:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/twtwosh.h"

static void		do_color(char *color, char *target)
{
	ft_putchar_fd('\033', 2);
	ft_putstr_fd(color, 2);
	ft_putstr_fd(target, 2);
}

static void		do_user(t_lst *list)
{
	char *user;

	user = NULL;
	user = get_content(list, "USER=");
	ft_putstr("# ");
	do_color(YELLOW, user);
	do_color(RESET, "");
	ft_putstr(" in ");
	//ft_strdel(&user);
}

static void		do_path(t_lst *list, char *buf)
{
	char *home;

	home = NULL;
	home = get_content(list, "HOME=");
	if (home && ft_strstr(buf, home))
	{
		do_color(GREEN, "");
		ft_putchar('~');
		ft_putstr(ft_strstr(buf, home) + ft_strlen(home));
		do_color(RESET, "");
	}
	else if (buf[0])
		ft_putstr(buf);
	do_color(RED, " \n$> ");
	do_color(RESET, "");
}

void			do_prompt(t_lst *list)
{
	char	*home;
	char	buf[100];

	home = NULL;
	ft_bzero(buf, 100);
	getcwd(buf, 100);
	do_user(list);
	do_path(list, buf);
}
