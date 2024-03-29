/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:11:20 by ada-mata          #+#    #+#             */
/*   Updated: 2024/02/02 17:25:50 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (!env || !env[0] || !env[2])
		{
			ft_printf("\033[31mError: No environment variables\n\e[0m");
			return (-1);
		}
		if (pipe(fd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(argv, env, fd);
		waitpid(pid, NULL, 0);
		parent_process(argv, env, fd);
	}
	else
		ft_printf("\033[31mError: Bad arguments\n\e[0m");
	return (0);
}
