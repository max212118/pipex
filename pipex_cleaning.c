/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:16:13 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/25 18:03:48 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex_cmds(t_pipex	*pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->cmds[i])
	{
		j = 0;
		while (pipex->cmds[i][j])
		{
			free(pipex->cmds[i][j]);
			j++;
		}
		free(pipex->cmds[i]);
		i++;
	}
	free(pipex->cmds);
}

void	free_pipex_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->cmds)
		free_pipex_cmds(pipex);
	if (pipex->paths)
		free_pipex_paths(pipex);
	if (pipex->current_cmd)
		free(pipex->current_cmd);
}
