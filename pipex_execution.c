/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:07:33 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/25 19:29:44 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	try_open_in(t_pipex *pipex)
{
	pipex->infile = open(pipex->av[1], O_RDONLY, 0644);
	if (pipex->infile == -1)
		(perror("infile error"), close(pipex->tube[0]),
			close(pipex->tube[1]), exit(EXIT_FAILURE));
}

void	try_open_out(t_pipex *pipex)
{
	pipex->outfile = open(pipex->av[pipex->cmd_number + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		(perror("outfile error"), exit(EXIT_FAILURE));
}

void	ft_execute(t_pipex	*pipex, int i)
{
	pipex->current_cmd = test_paths(pipex, i);
	if (!pipex->current_cmd)
		(perror("Command not found"), free_pipex(pipex), exit(EXIT_FAILURE));
	execve(pipex->current_cmd, pipex->cmds[i], pipex->envp);
	(perror("Erreur execution"), free_pipex(pipex), exit(EXIT_FAILURE));
}


void	ft_child_process(t_pipex *pipex, int i)
{
	close(pipex->tube[0]);
	if (i == 0)
	{
		try_open_in(pipex);
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}

	if (i == pipex->cmd_number - 1)
	{
		try_open_out(pipex);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	else
	{
		dup2(pipex->tube[1], STDOUT_FILENO);
		close(pipex->tube[1]);
	}
	ft_execute(pipex, i);
}

void	ft_parent_process(t_pipex *pipex, int i)
{
	close(pipex->tube[1]);
	if (i != pipex->cmd_number - 1)
		dup2(pipex->tube[0], STDIN_FILENO);
	close(pipex->tube[0]);
}
