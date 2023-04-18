/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systemcall1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyyoo <hyyoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:29:32 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/18 18:29:35 by hyyoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_errno("dup2()", strerror(errno), EXIT_FAILURE);
}

void	ft_pipe(int *fds)
{
	if (pipe(fds) == -1)
		exit_errno("pipe()", strerror(errno), EXIT_FAILURE);
}

pid_t	ft_fork(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
		exit_errno("fork()", strerror(errno), EXIT_FAILURE);
	return (ret);
}
