/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:53:06 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/18 22:01:58 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	first(t_cmd_info *tmp, t_cmd_info **ptr, t_cmd_info **head)
{
	tmp = (*ptr)->next;
	tmp->prev = NULL;
	(*head)->cmd_av = ft_free((*head)->cmd_av);
	*head = ft_free((*head));
	*head = tmp;
	*ptr = tmp;
}

void	ft_arg_check(t_cmd_info **cmd)
{
	t_cmd_info	*cur;
	t_cmd_info	*temp;

	cur = *cmd;
	temp = NULL;
	while (cur)
	{
		if (cur->prev == NULL && cur->next == NULL)
			return ;
		if (cur->ac == 0 && cur->prev == NULL && cur->ft_pipe_flag == 0)
			first(temp, &cur, cmd);
		else if (cur->ac == 0 && cur->ft_pipe_flag == 0)
		{
			temp = cur->prev;
			temp->next = cur->next;
			cur->cmd_av = ft_free(cur->cmd_av);
			cur = ft_free(cur);
			cur = temp->next;
			if (cur)
				cur->prev = temp;
		}
		else
			cur = cur->next;
	}
}
