/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:43:51 by ada-mata          #+#    #+#             */
/*   Updated: 2024/02/02 17:12:00 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libs/libft/libft.h"
# include "../libs/printf/ft_printf.h"

char	*find_path(char *cmd, char **envp);
void	exec_cmd(char *argv, char **envp);
void	error(void);
void	child_process(char **argv, char **env, int *fd);
void	parent_process(char **argv, char **env, int *fd);
#endif
