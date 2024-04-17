/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarnaud <mtarnaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:34 by mtarnaud          #+#    #+#             */
/*   Updated: 2024/04/17 20:25:49 by mtarnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex {
	char	***cmds;
	char	**paths;
	int		infile;
	int		outfile;
}	t_pipex;

char	**find_paths(char **env);
void	set_commands(int ac, char **av, t_pipex *pipex);
char	*ft_strjoin_three(char const *s1, char const *s2, const char *s3);
void	free_pipex(t_pipex	*pipex);
char	*test_paths(t_pipex	*pipex, int index_cmd);
void	ft_execve(t_pipex	*pipex, int id, int fd[2]);
void	ft_pipex(t_pipex	*pipex);
void	open_files(char **av, int ac, t_pipex	*pipex);

#endif
