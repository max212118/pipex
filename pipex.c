/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:25:02 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/25 19:27:41 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_pipex(int ac, char **av, t_pipex *pipex, char **envp)
{
	pipex->paths = find_paths(envp);
	if (!pipex->paths)
		(perror("No paths identify"), exit(EXIT_FAILURE));
	set_commands(ac, av, pipex);
	pipex->envp = envp;
	pipex->av = av;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->cmd_number = ac - 3;
}

void	ft_pipex(int ac, t_pipex *pipex, char **envp)
{
	int	i;
	int	pid;

	i = 0;
	while (i < pipex->cmd_number)
	{
		if (i < pipex->cmd_number - 1)
			pipe(pipex->tube);
		pid = fork();
		if (pid == 0)
			ft_child_process(pipex, i);
		else
			ft_parent_process(pipex, i);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int	i;

	i = 0;
	if (ac < 5)
		(perror(NULL), exit(EXIT_FAILURE));
	set_pipex(ac, av, &pipex, envp);
	ft_pipex(ac, &pipex, envp);
	while (i < pipex.cmd_number)
	{
		wait(NULL);
		i++;
	}
	(free_pipex(&pipex), exit(EXIT_SUCCESS));
}
