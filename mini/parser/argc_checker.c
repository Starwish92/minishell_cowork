/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argc_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyeongmin <yuhyeongmin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:57:20 by youjeon           #+#    #+#             */
/*   Updated: 2023/04/07 14:30:03 by yuhyeongmin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	first(t_cmd_info *tmp, t_cmd_info **ptr, t_cmd_info **head)
{
	tmp = (*ptr)->next;
	tmp->prev = NULL;
	(*head)->cmd_and_av = ft_frees((*head)->cmd_and_av);
	*head = ft_frees((*head));
	*head = tmp;
	*ptr = tmp;
}

void	argc_checker(t_cmd_info **cmd)
{
	t_cmd_info	*ptr;
	t_cmd_info	*tmp;

	tmp = NULL;
	ptr = *cmd;
	while (ptr)
	{
		if (ptr->prev == NULL && ptr->next == NULL)
			return ;
		if (ptr->ac == 0 && ptr->prev == NULL)
			first(tmp, &ptr, cmd);
		else if (ptr->ac == 0)
		{
			tmp = ptr->prev;
			tmp->next = ptr->next;
			ptr->cmd_and_av = ft_frees(ptr->cmd_and_av);
			ptr = ft_frees(ptr);
			ptr = tmp->next;
			if (ptr)
				ptr->prev = tmp;
		}
		else
			ptr = ptr->next;
	}
}
