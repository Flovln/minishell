/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:21:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/16 10:59:17 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <dirent.h>

#include "libft/libft.h"

#define DEBUG printf("%d: %s\n", __LINE__, __func__); /* ---DEBUG--- */

/*
typedef struct		s_exe
{
	char			*line;
	char			**cmd_path;
	char			**path_cpy;
}					t_exe;
*/

void	prompt(char **env);
char	*get_env_content(char **env, char *str);
void	exe_cmd(char **env, char **cmd, char **path_cpy);
char	*get_cmd_path(char *cmd, char **path);

/*
 * * Builtin Functions
 */

int		is_include(char **env, char *cmd);
int		is_builtin(char *cmd);
char	**do_builtin(char **cmd, char **env);
char	**do_cd(char **cmd, char **env);

char	**add_str(char **env, char **new_env, char **cmd, int len);
int		is_include(char **env, char *cmd);
char	**do_setenv(char **env, char **cmd);
char	**do_unsetenv(char **env, char **cmd);
char	**do_env(char **env, char **cmd);

/*
 * * Tools Functions
 */

char	**tab_dup(char **tab);
void	free_tab(char **tab);

#endif
