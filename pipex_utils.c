/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:33:28 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/17 20:19:36 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_three(char const *s1, char const *s2, const char *s3)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 1);
	if (!new)
		return (NULL);
	while (s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	i = 0;
	while (s3[i])
		new[j++] = s3[i++];
	new[j] = '\0';
	return (new);
}

char	**find_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (ft_split(env[i] + 5, ':'));
}

void	free_pipex(t_pipex	*pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
	{
		free(pipex->cmds[i]);
		i++;
	}
	free(pipex->cmds);
}

void	set_commands(int ac, char **av, t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	pipex->cmds = malloc(sizeof(char **) * (ac - 2));
	if (!pipex->cmds)
		exit (1);
	pipex->cmds[ac - 3] = NULL;
	while (j < ac - 1)
	{
		pipex->cmds[i] = ft_split(av[j], ' ');
		if (!pipex->cmds[i])
		{
			free_pipex(pipex);
			exit(1);
		}
		i++;
		j++;
	}
}

char	*test_paths(t_pipex	*pipex, int index_cmd)
{
	int		i;
	char	*command;

	i = 0;
	while (pipex->paths[i])
	{
		command = ft_strjoin_three(pipex->paths[i], "/",
				pipex->cmds[index_cmd][0]);
		if (access(command, F_OK | X_OK) == 0)
			return (command);
		i++;
		free(command);
	}
	return (NULL);
}