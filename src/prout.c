/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:29:31 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/20 13:42:40 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**ft_tabdup(char **tab)
{
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tmp[i] = ft_strdup(tab[i]);
		if (!tmp[i])
			return (NULL);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

void	init_struct(t_data *data, char **envp)
{
	data->env = ft_tabdup(envp);
	if (!data->env)
		return ;
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

void	build_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
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

void	unset_env(t_data *data, char *var)
{
	char	**newenv;
	int		newsize;
	int		i;
	int		j;

	newsize = ft_tablen(data->env) - ft_tablen(data->input) + 1;
	newenv = (char **)malloc(sizeof(char *) * (newsize));
	if (!newenv)
		return ;
	i = 0;
	j = 0;
	while (data->env[j])
	{
		if (ft_strncmp(var, data->env[j], ft_strlen(var)) == 0
			&& data->env[i][ft_strlen(var)] == '=')
		{
			free(data->env[i]);
			i++;
			continue ;
		}
		newenv[j] = ft_strdup(data->env[i]);
		i++;
		j++;
	}
	newenv[j] = NULL;
	malloc_free(data->env);
	data->env = ft_tabdup(newenv);
	if (!data->env)
		return ;
	malloc_free(newenv);
}

void	add_export(t_data *data)
{
	char	**newenv;
	int		newsize;
	int		i;
	int		j;

	newsize = ft_tablen(data->env) + ft_tablen(data->input);
	newenv = (char **)malloc(sizeof(char *) * (newsize));
	if (!newenv)
		return ;
	i = 0;
	while (data->env[i])
	{
		newenv[i] = ft_strdup(data->env[i]);
		if (!newenv[i])
			return ;
		i++;
	}
	j = 1;
	while (data->input[j])
	{
		// unset_env(data, data->input[j]);
		newenv[i] = ft_strdup(data->input[j]);
		if (!newenv[i])
			return ;
		i++;
		j++;
	}
	newenv[i] = NULL;
	malloc_free(data->env);
	data->env = ft_tabdup(newenv);
	if (!data->env)
		return ;
	malloc_free(newenv);
}

void	build_export(t_data *data)
{
	int		i;

	i = 0;

	if (ft_tablen(data->input) > 1)
		add_export(data);
	if (ft_tablen(data->input) == 1)
	{
		data->exp = ft_tabdup(data->env);
		if (!data->exp)
			return ;
		print_export(data);
		malloc_free(data->exp);
	}
}

void	build_unset(t_data *data)
{
	int	i;
	int	j;

	j = 1;
	while (j < ft_tablen(data->input))
	{
		i = 0;
		while (data->env[i])
		{
			if (ft_strncmp(data->input[j], data->env[i], \
				ft_strlen(data->input[j])) == 0
				&& data->env[i][ft_tablen(data->input)] == '=')
			{
				printf("{%s}\n", data->env[i]);
				free(data->env[i]);
				while (data->env[i + 1])
				{
					data->env[i] = data->env[i + 1];
					i++;
				}
				data->env[i] = NULL;
			}
			i++;
		}
		j++;
	}
}

void	parse_line(t_data *data, char *line)
{
	// init_struct(data);
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
		build_env(data);
	if (ft_strcmp(*data->input, "export") == 0)
		build_export(data);
	if (ft_strcmp(*data->input, "unset") == 0)
		build_unset(data);
	malloc_free(data->input);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_data	data;

	init_struct(&data, envp);
	line = readline("minishell $> ");
	while (line)
	{
		parse_line(&data, line);
		if (ft_strcmp(line, "exit") == 0)
		{
			if (data.env)
				malloc_free(data.env);
			return (0);
		}
		free(line);
		line = readline("minishell $> ");
	}
	(void)av;
	(void)ac;
	if (data.input)
		malloc_free(data.input);
	if (data.exp)
		malloc_free(data.exp);
	if (data.env)
		malloc_free(data.env);
}

//plusieurs export
//unset avnat d'export
