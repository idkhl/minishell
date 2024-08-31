/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:30:22 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/31 16:14:16 by idakhlao         ###   ########.fr       */
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
	char	**env;
	char	**exp;
	char	**path;
	int		heredoc;
	int		fd[2];
}	t_data;

void	handle_signals(void);
void	heredoc_signals(void);
// void	expand(t_data *data);
char	*access_cmd(t_data *data, char **tab);
char	**get_path(t_data *data);

/*	EXEC & REDIRECTIONS	*/

void	execute_cmd(t_data *data, char **tab);
// void	execute_cmd_out(t_data *data);
// void	execute_cmd_in(t_data *data);

/*	BUILT-INS	*/

int		check_builtins(t_data *data, char **tab);
void	build_echo(char **tab);
void	build_pwd(void);
void	build_cd(char **line);
void	build_env(t_data *data);
void	build_export(t_data *data, char **tab);
void	build_unset(t_data *data, char **tab);
void	build_exit(t_data *data, char **tab);

/*	UTILS	*/

int		ft_tablen(char **tab);
char	**ft_tabdup(char **tab);
char	**split_quotes(char *line, char c);
char	**split_pipes(char *line);
int		count_blocks(char *line);
char	***get_big_tab(char *line);

#endif