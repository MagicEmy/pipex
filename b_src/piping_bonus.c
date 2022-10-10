/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   piping.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 17:35:17 by emlicame      #+#    #+#                 */
/*   Updated: 2022/09/22 20:32:50 by emlicame      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	waiting(int id)
{
	int	status;
	int	exit_code;

	exit_code = -1;
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = (WEXITSTATUS(status));
		exit(exit_code);
	}
}

void	get_arg_path(t_variables *var, int i)
{
	var->arg_path = ft_split(var->argv[i], ' ');
	if (!var->arg_path)
		error_exit("Malloc failed", 1);
	if (!var->arg_path[0])
		perror ("command not found");
}

void	piping_loop(char **envp, t_variables *var)
{
	pid_t	id;
	int		fdd;

	fdd = -1;
	while (var->cmd < var->argc - 1)
	{
		if (pipe(var->pipe_fd) == -1)
			error_exit("Pipe failed", 1);
		id = fork();
		if (id == -1)
			error_exit("Fork failed", 1);
		if (id == 0)
		{
			get_arg_path(var, var->cmd);
			child_process(envp, var, fdd);
		}
		else
		{
			close(fdd);
			fdd = var->pipe_fd[0];
			parent_process(var);
		}
		var->cmd++;
	}
	waiting(id);
}
