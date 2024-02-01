/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:33:07 by ada-mata          #+#    #+#             */
/*   Updated: 2024/02/01 17:43:03 by ada-mata         ###   ########.fr       */
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
# include "./libs/libft/libft.h"
# include "./libs/printf/ft_printf.h"

char *find_path(char *cmd, char **envp);
void execute(char *argv, char **envp);
void error();
#endif
