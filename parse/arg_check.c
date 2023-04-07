/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngjpa <youngjpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:53:06 by youngjpa          #+#    #+#             */
/*   Updated: 2023/04/07 15:15:12 by youngjpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
