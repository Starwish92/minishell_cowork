/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:45:55 by mher              #+#    #+#             */
/*   Updated: 2023/04/07 14:30:03 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_need_fork(t_cmd_info *cmd)
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
			if (cmd->cmd_and_av[i][j] == -74)
				cmd->cmd_and_av[i][j] = '<';
			else if (cmd->cmd_and_av[i][j] == -76)
				cmd->cmd_and_av[i][j] = '>';
			++j;
		}
		++i;
	}
}
