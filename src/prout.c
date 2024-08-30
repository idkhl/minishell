/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/08/30 20:26:17 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	// data->input = NULL;
	data->exp = NULL;
	data->path = NULL;
}

// void	pipex(t_data *data)
// {
// 	int	infile;

// 	execute_cmd(data);
// 	infile = open(data->input[4], O_RDONLY, 0644);
// 	if (dup2(infile, STDIN_FILENO) == -1)
// 		return (close(infile), perror("dup2"));
// }

char	***get_big_tab(char *line)
{
	char	***result;
	int		i;
	int		nb_blocks;
	char	**tab;

	i = 0;
	tab = split_pipes(line);
	if (!tab)
		return (NULL);
	nb_blocks = count_blocks(line);
	result = (char ***)malloc((nb_blocks + 1) * sizeof(char **));
	if (!result)
	{
		perror("allocation failed\n");
		return (free(tab), NULL);
	}
	while (i < nb_blocks)
	{
		result[i] = split_quotes(tab[i], ' ');
		if (!result[i])
			return (malloc_free(tab), NULL);
		i++;
	}
	malloc_free(tab);
	return (result);
}

void	parse_line(t_data *data, char *line)
{
	int		i;
	int		nb_blocks;
	char	***big_tab;

	if (ft_strlen(line) == 0)
		return ;
	big_tab = get_big_tab(line);
	if (!big_tab)
		return ;
	nb_blocks = count_blocks(line);

	// i = 0;
	// while (i < nb_blocks)
	// {
	// 	int j = 0;
	// 	printf("INDEX I :%d\n", i);
	// 	while (big_tab[i][j])
	// 	{
	// 		printf("Bloc %d: [%s]\n", j + 1, big_tab[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }

	// expand(data);
	i = 0;
	while (i < nb_blocks)
	{
		if (check_builtins(data, big_tab[i]) == 0)
		{
			execute_cmd(data, big_tab[i]);
			malloc_free(data->path);
		}
		// if (nb_blocks > 1)
		// {
		// 	pipex(data, big_tab[i]);
		// }
		i++;
	}
	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '>')
	// {
	// 	execute_cmd_out(data);
	// 	malloc_free(data->path);
	// }
	// else if (ft_tablen(data->input) > 1 && *data->input[1] == '<')
	// {
	// 	execute_cmd_in(data);
	// 	malloc_free(data->path);
	// }
	// else
	// {
	// 	execute_cmd(data);
	// 	malloc_free(data->path);
	// }
	// if (ft_tablen(data->input) > 3 && *data->input[2] == '|')
	// {
	// 	pipex(data);
	// }
	i = 0;
	if (big_tab)
	{
		while (i < nb_blocks)
		{
			malloc_free(big_tab[i]);
			i++;
		}
		free(big_tab);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	handle_signals();
	line = readline("minishell $> ");
	while (line)
	{
		add_history(line);
		parse_line(&data, line);
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
}

// export a b -> export X env
//			pas de chiffres  symboles avant =
//			export les autres var si la 1ere existe deja
// echo var qui n'existe pas -> \n 
// var sans commandes

// line = /n || isspace
// sigignore dans le parent