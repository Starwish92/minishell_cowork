/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:03:42 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:47:11 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_frees(void *ptr)
{
	if (ptr)
	{
		free(ptr);
	}
	return (NULL);
}

t_cmd_info	*ft_list_init(void)
{
	t_cmd_info	*new_mem;

	new_mem = malloc(sizeof(t_cmd_info));
	new_mem->ac = 0;
	new_mem->cmd_and_av = NULL;
	new_mem->ft_dollar_flag = false;
	new_mem->fd[0] = -2;
	new_mem->fd[1] = -2;
	new_mem->ft_in_files = -2;
	new_mem->ft_out_files = -2;
	new_mem->ft_command_path = NULL;
	new_mem->ft_pipe_flag = false;
	new_mem->next = NULL;
	new_mem->prev = NULL;
	return (new_mem);
}

void	ft_free_list(t_cmd_info *cmd)
{
	t_cmd_info	*ptr;
	int		i;

	while (cmd)
	{
		i = 0;
		while (i < cmd->ac)
		{
			cmd->cmd_and_av[i] = ft_frees(cmd->cmd_and_av[i]);
			i++;
		}
		cmd->cmd_and_av = ft_frees(cmd->cmd_and_av);
		ptr = cmd;
		cmd = cmd->next;
		ptr = ft_frees(ptr);
	}
}
