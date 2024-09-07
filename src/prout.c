/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/09/07 19:40:21 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
	data->exp = NULL;
	data->path = get_path(data);
}

void	parse_line(t_data *data, char *line)
{
	int		nb_blocks;
	char	***big_tab;

	// sert juste pour quand realine est vide pcq sinon segfault
	// pas sure que ca match avec le parsing et la syntaxe
	if (ft_strlen(line) == 0)
		return ;

	big_tab = get_big_tab(line);
	if (!big_tab)
		return ;
	nb_blocks = count_blocks(line);
	if (nb_blocks == 1) //si pas de pipe
	{
		if (check_builtins(data, *big_tab) == 0) //si pas un builtin alors une cmd
			execute_cmd(data, *big_tab);
	}
	else
		pipex(data, big_tab, nb_blocks);
	free_tab(big_tab, nb_blocks);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	handle_signals(); // a refaire->ne marche bien que si tout est ok et que dans le parent
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



// export a b -> export X env
//			pas de chiffres  symboles avant =
//			export les autres var si la 1ere existe deja
// echo var qui n'existe pas -> \n 
// var sans commandes

// line = /n || isspace
// sigignore dans le parent



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