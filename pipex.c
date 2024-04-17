/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:25:02 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/17 20:25:39 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve(t_pipex	*pipex, int id, int fd[2])
{
	char	*cmd;
	int		status;

	if (id == 0)
	{
		close(fd[0]);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		cmd = test_paths(pipex, 0);
		if (!cmd)
			exit(3);
		execve(cmd, pipex->cmds[0], NULL);
	}
	else
	{
		waitpid(id, &status, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipex->outfile, STDOUT_FILENO);
		close(fd[0]);
		cmd = test_paths(pipex, 1);
		if (!cmd)
			exit(3);
		execve(cmd, pipex->cmds[1], NULL);
	}
}

void	ft_pipex(t_pipex	*pipex)
{
	int	fd[2];
	int	id;

	pipe(fd);
	id = fork();

	if (id == -1)
	{
		perror("Could not fork");
		exit(1);
	}
	ft_execve(pipex, id, fd);
}

void	open_files(char **av, int ac, t_pipex	*pipex)
{
	pipex->infile = open(av[1], O_RDONLY);
	if (pipex->infile == -1)
		exit(EXIT_FAILURE);
	pipex->outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac < 5)
	{
		perror("Wrong number of arguments\n");	
		return (-1);
	}
	open_files(av, ac, &pipex);
	set_commands(ac, av, &pipex);
	pipex.paths = find_paths(env);
	if (!pipex.paths)
	{
		printf("Can't create paths\n");
		return (-1);
	}
	ft_pipex(&pipex);
	return (0);
}