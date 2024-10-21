/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:30:22 by idakhlao          #+#    #+#             */
/*   Updated: 2024/10/21 18:42:25 by idakhlao         ###   ########.fr       */
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
	int		copy_stdin;
	int		copy_stdout;
}	t_data;

typedef struct s_input
{
	char	*input;
	char	**cmd;
	char	*in_file;
	char	*out_file;
	char	*redir_infile;
	char	*redir_outfile;
	int		fd_in;
	int		fd_out;
	int		heredoc;
}	t_input;

void	handle_signals(void);
void	heredoc_signals(void);
void	handle_heredoc_signals(void);
void	reset_signals_for_child(void);
void	handle_sigint(int sig);
void	expand(t_data *data, char **tab);

/*	EXEC & REDIRECTIONS	*/

void	execute_cmd(t_data *data, t_input *input, char **tab);
int		exec_builtins(t_data *data, char **tab);
void	pipex(t_data *data, t_input *input, int nb_blocks);
void	redir(t_data *data, t_input *input, int i);
void	heredoc(t_input *input, int i);
void	pipe_heredoc(t_data *data, t_input *input, int nb);
void	unlink_heredoc(t_input *input, int nb);
void	do_redir(t_data *data, t_input *input);

/*	BUILT-INS	*/

int		check_builtins(char **tab);
void	build_echo(char **tab);
void	build_pwd(void);
void	build_cd(char **line);
void	build_env(t_data *data);
void	build_export(t_data *data, char **tab);
void	build_unset(t_data *data, char **tab);
void	unset_var(t_data *data, int i);
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
int		count_cmds(char **tab);
// void	skip_redir(t_input *input, char *line);
char	*ft_structcpy(char *dest, char *src, int i);
int		get_len2(char *s);


/*  PARSING  */

char	*ft_strcpy(char *dest, char *src);
void	free_strings(char **strs);
void	ft_path(void);
int		ft_isspace(int c);
int		no_word_string(char *line);
int		check_quotes(char *line);
int		check_open_operators(char *line);
int		check_close_operators(char *line);
int		check_begin_pipes(char *line);
int		check_end_pipes(char *line);
int		check_nb_pipes(char *line);
int		check_syntax(char *line);
void	find_first_redir(t_input *tab, char **big_tab);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*quotecpy(char *dest, char *src, int n, char quote);
void	allocate_new_struct(t_input **tab, char *line);
void	fill_input(t_input *input, char *line);
void	init_struct(t_data *data, t_input *tab, char **envp);
int		count_words(char *line, char c);
int		allocate_and_copy_redir(char *s);

int		find_quotes(char *s, int i);
int		find_redirection(char *s, int i);
int		get_redirection_length(char *s);
char	*get_redir_type(char *s, int index);
int		get_redirection_start(char *s);
void	store_redir_symbols(t_input *input);
void	store_redir_symbols2(t_input *input);
void	store_redirection(t_input *input);
void	store_redirection2(t_input *input);
int		count_cmd(char *s);
void	fill_cmd(t_input *input);
int		get_len_in_quotes(char *s);
int		get_len(char *s);

int		skip_redir(char *s, int i);
void	fill_cmd(t_input *input);
void	allocate_cmds(t_input *input, int i);
void	process_input(t_input *input, int i);
int		handle_quotes_in_cmd(t_input *input, int i, int *k, int j);
int		handle_word(t_input *input, int i, int *k, int j);
void	fill_struct(t_input *input, char *line);

int		get_tab_len(char *s);
int		len_with_quote(char *str);
void	fill_tab(t_input *input);
int		get_index_redir(t_input *input, int *j);
int		get_nb_cmd(t_input *input);
char	*join_str(char *s1, char *s2);
char	*join_char(char *s1, char c);

#endif