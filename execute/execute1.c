/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:29:09 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/19 14:38:09 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(const char *file, char *const *argv, char *const *envp)
{
	if (!ft_strcmp(argv[0], "") && !argv[1])
	{
		exit(0);
		return ;
	}
	if (execve(file, argv, envp) == -1)
		exit_errno("execve()", strerror(errno), 126);
	return ;
}
