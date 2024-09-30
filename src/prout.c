/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/30 15:43:32 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, t_input *input, char **envp)
{
	int	i;

	i = 0;
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = get_path(data);
	if (input == NULL)
		return ;
	input->input = NULL;
	input->cmd = NULL;
	input->in_file = NULL;
	input->out_file = NULL;
	input->redir_infile = NULL;
	input->redir_outfile = NULL;
	input->fd_in = -1;
	input->fd_out = -1;
}

void	parse_line(t_data *data, t_input *input, char *line)
{
	int		nb_blocks;
	// char	***big_tab;

	// sert juste pour quand readline est vide pcq sinon segfault
	// pas sure que ca match avec le parsing et la syntaxe
	// if (ft_strlen(line) == 0)
	// 	return ;
	// big_tab = get_big_tab(line);
	// if (!big_tab)
	// 	return ;
	nb_blocks = count_blocks(line);
	if (nb_blocks == 1)
	{
		if (check_builtins(data, input->cmd) == 0)
			execute_cmd(data, input, input->cmd);
	}
	else
		pipex(data, input, nb_blocks);
	// free_tab(big_tab, nb_blocks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;
	t_input	*input = NULL;
	// int i;
	// int j;

	handle_signals(); // a refaire->ne marche bien que si tout est ok et que dans le parent
	line = readline("minishell $> ");
	init_struct(&data, input, envp);
	while (line)
	{
		add_history(line);
		allocate_new_struct(&input, line);
		fill_input(input, line);
		store_redir_symbols(input);
		store_redir_symbols2(input);
		store_redirection(input);
		store_redirection2(input);
		fill_cmd(input);
		// printf("input : %s\n", input[0].input);
		// printf("len inn quotes : %d\n", get_len_in_quotes(input[0].input));
		// printf("NB CMD = %d\n", count_cmd(input[0].input));
		// i = 0;
		// while (input[0].cmd[i])
		// {
		// 	printf("CMD [%d]: %s\n", i, input[0].cmd[i]);
		// 	i++;
		// }
		if (check_syntax(line) == 0)
			parse_line(&data, input, line);
		// check_syntax(line);
		// i = 0;
		// int index = find_redirection(input[0].input);
		// printf("length = %d\n", get_redirection_length(input[0].input));
		// printf("index redir = %d\n", find_redirection(input[0].input));
		// printf("redirection = %s\n", get_redir_type(input[0].input, index));
		// printf("index name redir %d\n", get_redirection_start(input[0].input));
		//printf("redir_infile %s\n", input[0].redir_infile);
		// printf("add redir struct %d\n", add_redir_struct(input));
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.env)
		malloc_free(data.env);
	malloc_free(data.path);
}


// IDEE(nulle) POUR LES REDIR
// - parcourir le char** juste avant d'executer pour voir s'il y en a
// - si non on continue l'exec normalement
// - si oui -> une fonction qui va identifier si elles sont avant la commande ou apres par ex: < infile > test cat > outfile 
// - on les mets dans deux char** un pour avant, un pour apres
// ex : [< infile][> test] d'un cote [> outfile] de l'autre
// - modifier le char ** de base pour ne garder que la commande pour execve
// -> si on tombe sur une redirection la free et free l'element d'apres qui sera forcement un fichier
// - faire les premieres redirections avant l'exec et la derniere apres l'exec
// -> si plusieurs redirections a la suite, faire une boucle sur le char**
// VOIR REDIR.C pour le plan du code
// Demander au joker s'il pense que c'est faisable/une bonne idee
// -> si oui: on tente
// -> si non: le frapper

// PRINT BIGTAB
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