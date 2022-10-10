/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:40:08 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/10 16:32:30 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*seeking_path(char **env)
{
	char	*get_path;
	char	*path;
	int		i;

	i = 0;
	get_path = "PATH=";
	while (env[++i] != NULL)
	{
		if (ft_memcmp(get_path, env[i], 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			if (!path)
				exit(0);
		}
	}
	return (path);
}

void	get_path(char **env, t_variables *var)
{
	int		i;
	char	**split_path;
	char	*my_path;

	i = -1;
	my_path = seeking_path(env);
	if (!my_path)
	{
		var->cmd_path = ft_split("", ' ');
		if (!var->cmd_path)
			error_exit("Malloc failed", 1);
	}
	else
	{
		split_path = ft_split(my_path, ':');
		free (my_path);
		if (!split_path)
			error_exit("Malloc failed", 1);
		while (split_path[++i])
			split_path[i] = ft_strjoin_withfree(split_path[i], "/");
		var->cmd_path = split_path;
	}
}

void	error_exit(char *text, int exit_code)
{
	perror(text);
	exit(exit_code);
}

void	checkleaks(void)
{
	system("leaks -q pipex");
	// system("lsof -c pipex");
}
	// atexit(checkleaks);

int	main(int argc, char **argv, char **envp)
{
	t_variables	var;

	if (argc != 5)
		error_exit("The number of arguments required is 4", 1);
	var.cmd = 2;
	var.argc = argc;
	var.argv = argv;
	get_path(envp, &var);
	piping_loop(envp, &var);
	return (0);
}
