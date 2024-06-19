/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/18 20:02:21 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_struct(t_data *data)
{
	// data->env = NULL;
	data->input = NULL;
	data->exp = NULL;
}

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

void	build_echo(t_data *data)
{
	int	i;
	int	nl;

	i = 0;
	nl = 0;
	if (ft_strcmp(data->input[i], "echo") == 0)
		i++;
	while (data->input[i] && ft_strncmp(data->input[i], "-n", 2) == 0)
	{
		nl = check_echo(data->input[i]);
		i++;
	}
	if (data->input[i])
	{
		while (data->input[i])
		{
			printf("%s", data->input[i]);
			if (data->input[i + 1])
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

void	build_cd(t_data *data)
{
	char	*s;

	s = "error";
	if (!data->input[1])
		return ;
	if (chdir(data->input[1]) != 0)
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

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	print_export(t_data *data)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (data->exp[i] != 0)
	{
		j = i;
		while (data->exp[j] != 0)
		{
			if (ft_strcmp(data->exp[i], data->exp[j]) > 0)
			{
				temp = data->exp[i];
				data->exp[i] = data->exp[j];
				data->exp[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = -1;
	while (data->exp[++i])
		printf("export %s\n", data->exp[i]);
}

void	add_export(t_data *data)
{
	printf("[%s]\n", data->input[1]);
}

void	build_export(t_data *data, char **envp)
{
	int		i;

	i = 0;

	data->exp = (char **)malloc(sizeof(char *) * (tab_len(envp) + 1));
	if (!data->exp)
		return ;
	while (envp[i])
	{
		data->exp[i] = ft_strdup(envp[i]);
		if (!data->exp[i])
			return ;
		i++;
	}
	data->exp[i] = NULL;
	if (tab_len(data->input) > 1)
		add_export(data);
	else
	{
		print_export(data);
	}
}

void	parse_line(t_data *data, char *line, char **envp)
{
	init_struct(data);
	data->input = ft_split(line, ' ');
	if (!data->input)
		return ;
	if (ft_strcmp(*data->input, "echo") == 0)
		build_echo(data);
	if (ft_strcmp(*data->input, "pwd") == 0)
		build_pwd();
	if (ft_strcmp(*data->input, "cd") == 0)
		build_cd(data);
	if (ft_strcmp(*data->input, "env") == 0)
		build_env(envp);
	if (ft_strcmp(*data->input, "export") == 0)
		build_export(data, envp);
	// malloc_free(tab);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	*data;

	data = NULL;
	line = readline("minishell $> ");
	while (line)
	{
		parse_line(data, line, envp);
		if (ft_strcmp(line, "exit") == 0)
			exit(0);
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
}
