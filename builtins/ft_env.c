/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shane <shane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:28:33 by hyyoo             #+#    #+#             */
/*   Updated: 2023/04/19 15:42:41 by shane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env_info *cur)
{
	while (cur->env_key != 0)
	{
		if (!ft_strcmp(cur->env_val, "don't"))
			cur = cur->next;
		else
		{
			ft_write(STDOUT_FILENO, cur->env_key, ft_strlen(cur->env_key));
			ft_write(STDOUT_FILENO, "=", 1);
			ft_write(STDOUT_FILENO, cur->env_val, ft_strlen(cur->env_val));
			ft_write(STDOUT_FILENO, "\n", 1);
			cur = cur->next;
		}
	}
	return (EXIT_SUCCESS);
}
