/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:40 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_size(char **tab)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (tab[i])
	{
		if (tab[i][0] != '>' && tab[i][0] != '<')
			size++;
		else
			i++;
		i++;
	}
	return (size);
}

char    **remove_redir(char **tab)
{
	char    **tmp;
    int     i;
    int     j;
    int     size;
	
    i = 0;
    j = 0;
	size = redir_size(tab);
    tmp = (char **)malloc(sizeof(char *) * (size + 1));
    if (!tmp)
        return (NULL);
    while (tab[i])
    {
        if (tab[i][0] != '>' && tab[i][0] != '<')
        {
            tmp[j] = ft_strdup(tab[i]);
            if (!tmp[j])
                return (malloc_free(tmp), NULL);
            j++;
        }
        else
            i++;
        i++;
    }
    tmp[j] = NULL;
    return (tmp);
}

void	exec_redir_out(char *sym, char *file)
{
	int	outfile;
	
	if (ft_strcmp(sym, ">") == 0)
		outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ft_strcmp(sym, ">>") == 0)
		outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
		return (perror("Open"));
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), perror("dup2"));
	close(outfile);
}

void	here_doc(t_redir *redir, char *eof)
{
	char	*line;

	line = readline("> ");
	redir->heredoc = open(".tmp_doc", O_WRONLY | O_CREAT | O_APPEND, 0600); //0644?
	if (redir->heredoc == -1)
		return ;
	while (line)
	{
		// heredoc_signals();
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		write(redir->heredoc, line, ft_strlen(line));
		write(redir->heredoc, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(redir->heredoc);
}

void	exec_redir_in(t_redir *redir, char *sym, char *file)
{
	int	infile;
	int	heredoc_infile;

	if (ft_strcmp(sym, "<") == 0)
	{
		infile = open(file, O_RDONLY);
		if (infile < 0)
			return (perror("Open"));
		if (dup2(infile, STDIN_FILENO) == -1)
			return (close(infile), perror("dup2"));
		close(infile);
	}
	if (ft_strcmp(sym, "<<") == 0)
	{
		here_doc(redir, file);
		heredoc_infile = open(".tmp_doc", O_RDONLY);
		if (heredoc_infile < 0)
			return (unlink(".tmp_doc"), perror("heredoc read open"));
		if (dup2(heredoc_infile, STDIN_FILENO) == -1)
			return (unlink(".tmp_doc"), close(heredoc_infile), perror("dup2"));
		close(heredoc_infile);
		unlink(".tmp_doc");
	}
}

void	exec_redir_before(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir->before[i])
	{
		if (*redir->before[i] == '>')
			exec_redir_out(redir->before[i], redir->before[i + 1]);
		if (*redir->before[i] == '<')
			exec_redir_in(redir, redir->before[i], redir->before[i + 1]);
		i += 2;
	}
}

void	exec_redir_after(t_redir *redir)
{
	int	i;

	i = 0;
	while (redir->after[i])
	{
		if (*redir->after[i] == '>')
			exec_redir_out(redir->after[i], redir->after[i + 1]);
		if (*redir->after[i] == '<')
			exec_redir_in(redir, redir->after[i], redir->after[i + 1]);
		i += 2;
	}
}

void exec_redir(t_redir *redir, char **redirection)
{
	int i = 0;

	while (redirection[i])
	{
		if (ft_strcmp(redirection[i], ">") == 0 || ft_strcmp(redirection[i], ">>") == 0)
			exec_redir_out(redirection[i], redirection[i + 1]);
		else if (ft_strcmp(redirection[i], "<") == 0 || ft_strcmp(redirection[i], "<<") == 0)
			exec_redir_in(redir, redirection[i], redirection[i + 1]);
		i += 2;
	}
}

void	execute_cmd(t_data *data, char **tab)
{
	char	*cmd;
	char	**tmp;
	t_redir	redir;
	pid_t	pid;

	// redirections(&redir, tab);
	tmp = remove_redir(tab);
	cmd = access_cmd(data, tmp);
	// print tmp -> uniquement la commande pas de redir
	int i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		i++;
	}
	if (!cmd)
		return (perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
	{
		// if (redir.before)
		// 	exec_redir(&redir, redir.before);
		// if (redir.after)
		// 	exec_redir(&redir, redir.after);
		if (execve(cmd, tmp, data->env) == -1)
			return (free(cmd), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
	}
	(void)redir;
}

