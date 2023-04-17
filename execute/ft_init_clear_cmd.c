/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_clear_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:01:14 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/17 19:41:04 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_here_init(t_cmd_info *cmd)
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

void	ft_clear_command(t_cmd_info *cmd)
{
	t_cmd_info	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->fd[READ] > 0)
			ft_close(cur->fd[READ]);
		if (cur->ft_in_files > 0)
			ft_close(cur->ft_in_files);
		if (cur->ft_out_files > 0)
			ft_close(cur->ft_out_files);
		if (cur->ft_command_path != NULL)
			cur->ft_command_path = ft_free(cur->ft_command_path);
		cur = cur->next;
	}
	ft_del_tmpfile();
}
