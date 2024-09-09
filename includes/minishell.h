/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inesdakhlaoui <inesdakhlaoui@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:30:22 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/09 18:39:24 by inesdakhlao      ###   ########.fr       */
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
void	expand(t_data *data, char **tab);

/*	EXEC & REDIRECTIONS	*/

void	execute_cmd(t_data *data, char **tab);
void	pipex(t_data *data, char ***big_tab, int nb_blocks);

void	redir(t_data *data, char **tab);
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

char	***get_big_tab(char *line);
char	**split_quotes(char *line, char c);
char	**split_pipes(char *line);

char	*access_cmd(t_data *data, char **tab);
char	**get_path(t_data *data);

int		count_blocks(char *line);
int		ft_tablen(char **tab);
char	**ft_tabdup(char **tab);
void	free_tab(char ***big_tab, int size);

#endif