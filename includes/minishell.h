/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:30:22 by idakhlao          #+#    #+#             */
/*   Updated: 2024/07/01 13:00:37 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_data
{
	char	**input;
	char	**env;
	char	**exp;
	char	**path;
}	t_data;

void	expand(t_data *data);
char	*access_cmd(t_data *data);
char	**get_path(t_data *data);

/*	BUILT-INS	*/

void	build_echo(t_data *data);
void	build_pwd(void);
void	build_cd(t_data *data);
void	build_env(t_data *data);
void	build_export(t_data *data);
void	build_unset(t_data *data);
void	build_exit(t_data *data);

/*	UTILS	*/

int		ft_tablen(char **tab);
char	**ft_tabdup(char **tab);

#endif