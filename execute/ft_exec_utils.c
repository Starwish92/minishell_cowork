/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:36 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/14 20:56:12 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_need_fork_cmd(t_cmd_info *cmd)
{
	if (cmd->prev != NULL)
		return (1);
	if (cmd->ft_pipe_flag == true)
		return (1);
	if (cmd->ft_in_files != -2)
		return (1);
	if (cmd->ft_out_files != -2)
		return (1);
	if (!ft_strcmp(cmd->cmd_and_av[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "export"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "unset"))
		return (0);
	if (!ft_strcmp(cmd->cmd_and_av[0], "exit"))
		return (0);
	return (1);
}

void	restore_redirection_char(t_cmd_info *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->cmd_and_av[i])
	{
		j = 0;
		while (cmd->cmd_and_av[i][j])
		{
			if (cmd->cmd_and_av[i][j] == REDIR_L)
				cmd->cmd_and_av[i][j] = '<';
			else if (cmd->cmd_and_av[i][j] == REDIR_R)
				cmd->cmd_and_av[i][j] = '>';
			++j;
		}
		++i;
	}
}

void	ft_close_not_use_fd(t_cmd_info *cmd, pid_t pid)
{
	if (pid != 0)
	{
		if (cmd->fd[WRITE] != -2)
			cmd->fd[WRITE] = ft_close(cmd->fd[WRITE]);
	}
	else
	{
		if (cmd->fd[READ] != -2)
			cmd->fd[READ] = ft_close(cmd->fd[READ]);
	}
	return ;
}

void	wait_child(void)
{
	int	status;
	int	signo;
	int	i;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			g_exit_signal_code = 128 + signo;
		}
		else
			g_exit_signal_code = WEXITSTATUS(status);
	}
}
