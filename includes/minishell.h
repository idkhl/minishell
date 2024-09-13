/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrikach <afrikach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:30:22 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/13 18:55:18 by afrikach         ###   ########.fr       */
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

// ex : < infile cat Makefile | ls | echo hello > outfile
// ci bas l'exemple pour le premier bloc

typedef	struct s_input
{
	char	*input; //< infile cat Makefile
	char	**tab; // [<][infile] [cat] [Makefile]
	char	**cmd; // [cat] [Makefile]
	char	*in_file; // [infile]
	char	*out_file;
	int		fd_in;
	int		fd_out;
}	t_input;

void	handle_signals(void);
void	heredoc_signals(void);
void	expand(t_data *data, char **tab);

/*	EXEC & REDIRECTIONS	*/

void	execute_cmd(t_data *data, char **tab);
void	pipex(t_data *data, char ***big_tab, int nb_blocks);
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

/*  PARSING  */

char	*ft_strcpy(char *dest, char *src);
void	free_strings(char **strs);
void    ft_path(void);
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
void	allocate_new_struct(t_input *tab, char *line);
void	fill_input(t_input *input, char *line);
void	init_struct(t_data *data, t_input *tab, char **envp);
int		count_words(char *line, char c);
void	allocate_and_copy_redir(t_input *input, char *line);

enum e_token
{
	SPACES = 1,
	HEREDOC,
	INPUT,
	APPEND,
	TRUNC,
	CMD,
	OPT, // -l -o -s etc..
	ARG, // ex: echo salut, salut est l'arg.
	PIPE,
	END,
};


#endif