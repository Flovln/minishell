/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 10:21:19 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/22 13:36:17 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <dirent.h>

# define RED "[31m"
# define GREEN "[32m"
# define YELLOW "[33m"
# define RESET "[39m"

void	prompt(char **env, int count);
void	manage_exe_cmd(char **env, char **cmd, char **path_cpy);
char	*get_cmd_path(char *cmd, char **path);
void	exe_fork(char **env, char **cmd, char *cmd_path);
char	**add_str(char **env, char **new_env, char **cmd, int len);
int		is_include(char **env, char *cmd);
int		is_builtin(char *cmd);
char	**do_builtin(char **cmd, char **env, int flag);
char	**do_cd(char **cmd, char **env);
char	**do_setenv(char **env, char **cmd);
char	**do_unsetenv(char **env, char **cmd, int flag);
char	**do_env(char **env, char **cmd);
char	**ignore_env(char **env, int len);
char	*get_env_content(char **env, char *str);
void	print_env(char **env);
char	**manage_do_env(char **env, char **cmd, char **tmp);
int		ft_occ_nb(char *s, char c);
char	*ft_strcdup(char *s, char c);
char	**setenv_redirection(char **env, char **cmd);
char	**resize_cmd(char **cmd, char **cmd_tmp, int flag);
void	fork_redirection(char **env, char **cmd, int flag);
void	fork_bis(char **env, char **cmd_tmp, char *cmd_path, char **path);
char	**tab_dup(char **tab);
int		ft_multi_strcmp(char *s, char *s1, char *s2);
void	free_tab(char **tab);
void	free_ptrs(char **env_cpy, char **cmd, char **path_cpy);
void	free_fork(char **path, char *cmd_path, char *path_str);
int		is_in(char **env, char *cmd);

#endif
