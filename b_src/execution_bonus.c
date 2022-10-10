/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 17:35:17 by emlicame      #+#    #+#                 */
/*   Updated: 2022/09/22 20:29:55 by emlicame      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_infile(t_variables *var)
{
	close(var->pipe_fd[0]);
	var->file1 = open(var->argv[1], O_RDONLY);
	if (var->file1 < 0)
		error_exit(var->argv[1], 1);
	if (dup2(var->file1, STDIN_FILENO) < 0)
		error_exit("Dup failed", 1);
	close(var->file1);
}

void	dup_outfile(t_variables *var)
{
	close(var->pipe_fd[1]);
	var->file2 = open(var->argv[var->argc -1], \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (var->file2 < 0)
		error_exit(var->argv[var->argc -1], 1);
	if (dup2(var->file2, STDOUT_FILENO) < 0)
		error_exit("Dup failed", 1);
	close(var->file2);
}

void	dup_pipes(t_variables *var)
{
	close(var->pipe_fd[0]);
	if (dup2(var->pipe_fd[1], 1) < 0)
		strerror(errno);
	close(var->pipe_fd[1]);
}

void	child_process(char **envp, t_variables *var, int fdd)
{
	if (var->cmd == 2)
	{
		dup_infile(var);
		if (dup2(var->pipe_fd[1], 1) < 0)
			error_exit("Dup failed", 1);
		close(var->pipe_fd[1]);
	}
	else if (var->cmd == var->argc - 2)
	{
		close(var->pipe_fd[0]);
		if (dup2(fdd, 0) < 0)
			error_exit("Dup failed", 1);
		close(fdd);
		dup_outfile(var);
	}
	else
	{
		if (dup2(fdd, 0) < 0)
			error_exit("Dup failed", 1);
		close(fdd);
		dup_pipes(var);
	}
	access_file(envp, var);
	executing_file(envp, var);
}

void	parent_process(t_variables *var)
{
	close(var->pipe_fd[1]);
	if (var->cmd == var->argc - 2)
		close(var->pipe_fd[0]);
}
