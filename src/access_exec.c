/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emlicame <emlicame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:38:44 by emlicame          #+#    #+#             */
/*   Updated: 2022/10/05 17:34:47 by emlicame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_all(t_variables *var, char *temp)
{
	free (temp);
	temp = NULL;
	ft_free_mem(var->cmd_path);
	var->cmd_path = NULL;
	ft_free_mem(var->arg_path);
	var->arg_path = NULL;
}

void	access_file(char **envp, t_variables *var)
{
	char	*temp;

	temp = NULL;
	if (access(var->arg_path[0], X_OK) == 0)
	{	
		temp = ft_strdup(var->arg_path[0]);
		if (!temp)
		{
			ft_free_all(var, temp);
			error_exit("Malloc failed", 1);
		}
		if (execve(temp, var->arg_path, envp) < 0)
		{
			ft_free_all(var, temp);
			error_exit("command not found", 127);
		}
	}
}

void	executing_file(char **envp, t_variables *var)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (var->cmd_path[i])
	{
		temp = ft_strjoin_withfree(var->cmd_path[i], var->arg_path[0]);
		if (!temp)
		{
			ft_free_all(var, temp);
			error_exit("Malloc failed", 1);
		}
		if (access(temp, X_OK) >= 0)
		{
			if (execve(temp, var->arg_path, envp) < 0)
				error_exit("command not found", 127);
		}
		i++;
	}
	if (access(temp, X_OK) < 0)
		error_exit("command not found", 127);
}
