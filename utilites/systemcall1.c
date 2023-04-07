/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systemcall1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:59:24 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:47:23 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(char *fname, int oflag, int mode)
{
	int	fd;

	fd = open(fname, oflag, mode);
	if (fd < 0)
		exit_with_err(fname, strerror(errno), EXIT_FAILURE);
	return (fd);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
		exit_with_err("close()", strerror(errno), EXIT_FAILURE);
	return (-2);
}

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit_with_err("dup2()", strerror(errno), EXIT_FAILURE);
}

void	ft_pipe(int *fds)
{
	if (pipe(fds) == -1)
		exit_with_err("pipe()", strerror(errno), EXIT_FAILURE);
}

pid_t	ft_fork(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
		exit_with_err("fork()", strerror(errno), EXIT_FAILURE);
	return (ret);
}
