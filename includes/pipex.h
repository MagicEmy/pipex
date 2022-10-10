/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 18:26:42 by emlicame      #+#    #+#                 */
/*   Updated: 2022/09/22 20:39:20 by emlicame      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //perror
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_elements
{
	int		file1;
	int		file2;
	int		cmd;
	int		argc;
	char	**argv;
	int		pipe_fd[2];
	char	**cmd_path;
	char	**arg_path;
}t_variables;

//path
char	*seeking_path(char **env);
void	get_path(char **env, t_variables *var);
void	get_arg_path(t_variables *var, int i);
void	executing_file(char **envp, t_variables *var);
void	access_file(char **envp, t_variables *var);

//pipe
void	parent_process(t_variables *var);
void	child_process(char **envp, t_variables *var, int fdd);
void	piping_loop(char **envp, t_variables *var);
void	error_exit(char *text, int exit_code);

//split and split_assist
size_t	ft_strlen(const char *s);
int		ft_free_mem(char **split);
char	*ft_strdup(const char *s1);
char	*ft_strjoin_withfree(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif