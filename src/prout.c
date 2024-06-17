/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/17 15:51:25 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_echo(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
		{
			printf("%s ", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	build_echo(char **tab)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	if (ft_strcmp(tab[i], "echo") == 0)
		i++;
	while (tab[i] && ft_strncmp(tab[i], "-n", 2) == 0)
	{
		nl = check_echo(tab[i]);
		i++;
	}
	if (tab[i])
	{
		while (tab[i])
		{
			printf("%s", tab[i]);
			if (tab[i + 1])
				printf(" ");
			i++;
		}
	}
	if (nl == 0)
		printf("\n");
}

void	build_pwd(void)
{
	char	buf[1000];
	char	*s;

	s = "error";
	if (getcwd(buf, 1000) == NULL)
		return (perror(s));
	printf("%s\n", buf);
}

void	build_cd(char **tab)
{
	char	*s;

	s = "error";
	if (chdir(tab[1]) != 0)
		return (perror(s));
}

void	build_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	parse_line(char *line, char **envp)
{
	char	**tab;

	tab = ft_split(line, ' ');
	if (!tab)
		return ;
	if (ft_strcmp(*tab, "echo") == 0)
		build_echo(tab);
	if (ft_strcmp(*tab, "pwd") == 0)
		build_pwd();
	if (ft_strcmp(*tab, "cd") == 0)
		build_cd(tab);
	if (ft_strcmp(*tab, "env") == 0)
		build_env(envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;

	line = readline("minishell $> ");
	while (line)
	{
		parse_line(line, envp);
		if (ft_strcmp(line, "exit") == 0)
			exit(0);
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
}
