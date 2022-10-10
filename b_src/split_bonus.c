/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: emlicame <emlicame@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/22 17:45:13 by emlicame      #+#    #+#                 */
/*   Updated: 2022/09/22 20:20:55 by emlicame      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split(char const *s, char c);
size_t	ft_count(char const *s, char c);
int		ft_alloc_copy(char const *s, char c, char **split, size_t elem);
int		ft_free_mem(char **split);

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	elem;

	if (!s)
		return (NULL);
	elem = ft_count(s, c);
	split = (char **)ft_calloc((elem + 1), (sizeof(char *)));
	if (!split)
		return (NULL);
	if (ft_alloc_copy(s, c, split, elem))
		return (0);
	return (split);
}

int	ft_alloc_copy(char const *s, char c, char **split, size_t elem)
{
	size_t		len;
	size_t		index;
	size_t		i;

	i = 0;
	index = 0;
	while (index < elem)
	{
		len = 0;
		while (s[i + len] != c && s[i + len] != '\0')
		{
			len++;
			if (s[i + len] == c || s[i + len] == '\0')
			{
				split[index] = ft_substr(s, i, len);
				if (!split[index++])
					ft_free_mem(split);
			}
		}
		i += len + 1;
	}
	split[index] = 0;
	return (0);
}

size_t	ft_count(char const *s, char c)
{
	int		i;
	size_t	elem;

	i = 0;
	elem = 0;
	if (s[i] != c && s[i] != '\0')
	{
		elem++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			elem++;
		i++;
	}
	return (elem);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*string;
	unsigned int	i;
	size_t			j;

	i = start;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	string = (char *)malloc(len + 1);
	if (string == NULL)
		return (string);
	j = 0;
	while (s[i] && j < len)
	{
		string[j] = s[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}

int	ft_free_mem(char **split)
{
	int	c;

	c = 0;
	if (!split || !*split)
		return (0);
	while (split[c])
	{
		free(split[c]);
		split[c++] = NULL;
	}
	free(split);
	split = NULL;
	return (1);
}

/*
int	main(void)
{
	char		c;
	int			x;
	char const	*s;
	char		**ptr;

	c = ' ';
	x = 0;
	s = "gg   gkgkgkuhi n;jhl g;j; hkg g lkj;k go";
	ptr = ft_split(s, c);
	while (ptr[x])
		printf("|%s|\n", ptr[x++]);
	return (0);
}
*/