/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_clear_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:40:14 by mher              #+#    #+#             */
/*   Updated: 2023/04/07 14:30:03 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	init_heredoc(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (heredoc(cur) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

void	clear_cmd(t_cmd_info *cmd_head)
{
	t_cmd_info	*cur;

	cur = cmd_head;
	while (cur)
	{
		if (cur->fd[READ] > 0)
			ft_close(cur->fd[READ]);
		if (cur->ft_in_files > 0)
			ft_close(cur->ft_in_files);
		if (cur->ft_out_files > 0)
			ft_close(cur->ft_out_files);
		if (cur->ft_command_path != NULL)
			cur->ft_command_path = ft_frees(cur->ft_command_path);
		cur = cur->next;
	}
	delete_tmp_file();
}
