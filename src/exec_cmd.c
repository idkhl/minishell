/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:36:50 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/24 12:26:37 by idakhlao         ###   ########.fr       */
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

char	**remove_redir(char **tab)
{
	char	**tmp;
	int		i;
	int		j;
	int		size;

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
				return (NULL);
			j++;
		}
		else
			i++;
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

void	execute_cmd(t_data *data, char **tab)
{
	char	*cmd;
	char	**tmp;
	pid_t	pid;

	// redir(data, tab);
	tmp = remove_redir(tab);
	cmd = access_cmd(data, tmp);
	// print tmp soit uniquement la commande pas de redir
	// int i = 0;
	// while (tmp[i])
	// {
	// 	printf("%s\n", tmp[i]);
	// 	i++;
	// }
	if (!cmd)
		return (perror("access_cmd"));
	pid = fork();
	if (pid < 0)
		return (free(cmd), perror("fork"));
	if (pid == 0)
	{
		if (execve(cmd, tmp, data->env) == -1)
			return (free(cmd), free(tmp), exit(EXIT_FAILURE));
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(cmd);
		free(tmp);
	}
}
